#include <common/comms.h>
#include <common/log/log.h>
#include <zconf.h>
#include <hiredis/adapters/libuv.h>

using namespace hades;

const auto log = LoggerProvider::get("Comms");
const std::string availableServicesTopic = "available-services";

static Communication *communicationCtx;

void Communication::dispose() {
    uv_stop(communicationCtx->loop_);
    delete communicationCtx;
}

void onRedisConnected(const redisAsyncContext *ctx, int status) {
    if (!status) {
        log->info("Redis server connected");
    }
}

void sendAvailability(uv_timer_t *data) {
    auto comms = static_cast<Communication *>(data->data);
    redisAsyncCommand(comms->client(), nullptr, nullptr, "PUBLISH %s %s", availableServicesTopic.c_str(),
                      comms->serviceName().c_str());
}

void Communication::threadCtx(void *ctx) {
    auto comms = static_cast<Communication *>(ctx);

    if (comms->listenClient()->err) {
        log->error("Failed to connect to Redis, error: %v", comms->listenClient()->err);
        return;
    }

    comms->listenClient()->data = ctx;
    comms->client()->data = ctx;

    uv_loop_init(comms->loop_);

    redisLibuvAttach(comms->listenClient(), comms->loop_);
    redisAsyncSetConnectCallback(comms->listenClient(), &onRedisConnected);

    redisLibuvAttach(comms->client(), comms->loop_);
    redisAsyncSetConnectCallback(comms->client(), &onRedisConnected);

    redisAsyncCommand(comms->listenClient(), [](redisAsyncContext *redis, void *r, void *ctx) {
        redisReply *reply = static_cast<redisReply *>(r);

        if (reply == NULL) return;

        if (reply->type == REDIS_REPLY_ARRAY) {
            if (reply->element[2]->str != NULL) {
                std::string topic(reply->element[1]->str);
                std::string data(reply->element[2]->str);

                if (topic == availableServicesTopic) {
                    log->info("service available: %v", data);
                } else {
                    auto ctx = static_cast<Communication *>(redis->data);
                    ctx->subscriber_->onMessage(ctx, 0, std::move(data), nullptr);
                }
             }
        }
    }, nullptr, "SUBSCRIBE available-services service:%s", comms->serviceName().c_str());

    uv_timer_t timer;
    uv_timer_init(comms->loop_, &timer);

    timer.data = comms;
    uv_timer_start(&timer, &sendAvailability, 500, 500);

    uv_run(comms->loop_, UV_RUN_DEFAULT);
}

void Communication::start(std::string serviceName, RedisConfig redisConfig,
                          std::unique_ptr<CommunicationSubscriber> subscriber) {
    communicationCtx = new Communication(serviceName, std::move(redisConfig), std::move(subscriber));
    uv_thread_create(communicationCtx->thread_, &Communication::threadCtx,
                     static_cast<void *>(communicationCtx));
}
