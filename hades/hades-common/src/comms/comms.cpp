#include <common/comms/comms.h>
#include <common/log/log.h>
#include <hiredis/adapters/libuv.h>
#include <common/util/base64.h>
#include <chrono>
#include <common/util/time.h>

using namespace hades;

const auto logger = LoggerProvider::get("ServiceComms");
const std::string availableServicesTopic = "available-services";

#define SERVICE_HEARTBEAT 500
#define SERVICE_TIMEOUT 750

static Communication *communicationCtx;

void Communication::createSubscription(redisAsyncContext *redis, void *r, void *ctx) {
    auto comms = static_cast<Communication *>(redis->data);
    auto *reply = static_cast<redisReply *>(r);

    if (reply == NULL) return;

    if (reply->type == REDIS_REPLY_ARRAY) {
        if (reply->element[2]->str != NULL) {
            std::string topic(reply->element[1]->str);
            redisReply *payload = reply->element[2];

            if (topic == availableServicesTopic) {
                comms->onServiceAvailable(std::string(payload->str));
            } else {
                comms->onMessage(payload);
            }
        }
    }
}

void Communication::dispose() {
    uv_stop(&communicationCtx->loop_);
    delete communicationCtx;
}

void onRedisConnected(const redisAsyncContext *ctx, int err) {
    if (!err) {
        logger->info("Redis server connected");
    }
}

void sendAvailability(uv_timer_t *data) {
    auto comms = static_cast<Communication *>(data->data);
    redisAsyncCommand(comms->client(), nullptr, nullptr, "PUBLISH %s %s", availableServicesTopic.c_str(),
                      comms->serviceName().c_str());
}

void checkAvailableServices(uv_timer_t *data) {
    auto comms = static_cast<Communication *>(data->data);
    auto currentTime = currentTimeMillis();

    RwLockGuard lock(comms->servicesLock(), WRITE);

    for (std::map<std::string, long>::iterator service = comms->services()->begin();
         service != comms->services()->end(); ++service) {
        long difference = currentTime - service->second;

        if (SERVICE_TIMEOUT < difference) {
            logger->info("service %v timed out (diff: %v)", service->first, difference);
            comms->services()->erase(service->first);
        }
    }
}

void Communication::onMessage(redisReply *payload) {
    size_t size = 0;
    const char *out = reinterpret_cast<const char *>(b64_decode_ex(payload->str, payload->len, &size));
    Buffer buffer(size, out, false);

    short msgType = buffer.read<short>();
    std::string id = buffer.read<std::string>();

    this->subscriber_->onMessage(this, msgType, std::move(id),
                                 std::make_unique<Buffer>(std::move(buffer)));
}

void Communication::onServiceAvailable(std::string serviceName) {
    RwLockGuard lock(&this->servicesLock_, WRITE);
    this->services_[serviceName] = currentTimeMillis();
}

void Communication::threadCtx(void *ctx) {
    auto comms = static_cast<Communication *>(ctx);

    if (comms->listenClient()->err) {
        logger->error("Failed to connect to Redis, error: %v", comms->listenClient()->err);
        return;
    }

    comms->listenClient()->data = ctx;
    comms->client()->data = ctx;

    uv_loop_init(&comms->loop_);

    redisLibuvAttach(comms->listenClient(), &comms->loop_);
    redisAsyncSetConnectCallback(comms->listenClient(), &onRedisConnected);

    redisLibuvAttach(comms->client(), &comms->loop_);
    redisAsyncSetConnectCallback(comms->client(), &onRedisConnected);

    redisAsyncCommand(comms->listenClient(), &createSubscription, nullptr, "SUBSCRIBE available-services service:%s",
                      comms->serviceName().c_str());

    uv_timer_t sendAvailabilityTimer;
    uv_timer_init(&comms->loop_, &sendAvailabilityTimer);

    uv_timer_t checkAvailabilityTimer;
    uv_timer_init(&comms->loop_, &checkAvailabilityTimer);

    sendAvailabilityTimer.data = comms;
    checkAvailabilityTimer.data = comms;

    uv_timer_start(&sendAvailabilityTimer, &sendAvailability, SERVICE_HEARTBEAT, SERVICE_HEARTBEAT);
    uv_timer_start(&checkAvailabilityTimer, &checkAvailableServices, SERVICE_TIMEOUT, SERVICE_TIMEOUT);

    redisAsyncCommand(comms->client(), nullptr, nullptr, "PUBLISH available-services kek-server");

    uv_run(&comms->loop_, UV_RUN_DEFAULT);
}

void Communication::start(std::string serviceName, RedisConfig redisConfig,
                          std::unique_ptr<CommunicationSubscriber> subscriber) {
    communicationCtx = new Communication(std::move(serviceName), std::move(redisConfig), std::move(subscriber));
    uv_thread_create(&communicationCtx->thread_, &Communication::threadCtx,
                     static_cast<void *>(communicationCtx));
}

void Communication::send(std::string serviceName, short type, std::string id, void (*writer)(Buffer *buf)) {
    std::unique_ptr<Buffer> payload = std::make_unique<Buffer>(256, true);

    payload->write<short>(type);
    payload->write<std::string>(id);

    writer(payload.get());

    const char *data = b64_encode(reinterpret_cast<const unsigned char *>(payload->base()),
                                  static_cast<size_t>(payload->writerIndex()));

    redisAsyncCommand(communicationCtx->client(), nullptr, nullptr, "PUBLISH service:%s %s", serviceName.c_str(), data);
}
