#include <common/comms.h>
#include <common/log/log.h>
#include <zconf.h>
#include <hiredis/adapters/libuv.h>

using namespace hades;

const auto log = LoggerProvider::get("Comms");

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

void Communication::threadCtx(void *ctx) {
    // - create loop
    // - subscribe to topic
    // - parse data, dispatch msg to subscriber
    // - run loop
    // - free comms obj
    auto comms = static_cast<Communication *>(ctx);

    if (comms->redis()->err) {
        log->error("Failed to connect to Redis, error: %v", comms->redis()->err);
        return;
    }

    comms->redis()->data = ctx;
    uv_loop_init(comms->loop_);

    redisLibuvAttach(comms->redis(), comms->loop_);
    redisAsyncSetConnectCallback(comms->redis(), &onRedisConnected);

    redisAsyncCommand(comms->redis(), [](redisAsyncContext *redis, void *reply, void *data) {
        auto ctx = static_cast<Communication *>(redis->data);

        ctx->subscriber_->onMessage(ctx, 1337, "msg", nullptr);
    }, nullptr, "SUBSCRIBE test");

    uv_run(comms->loop_, UV_RUN_DEFAULT);
}

void Communication::start(std::string serviceName, RedisConfig redisConfig, std::unique_ptr<CommunicationSubscriber> subscriber) {
    communicationCtx = new Communication(serviceName, std::move(redisConfig), std::move(subscriber));
    uv_thread_create(communicationCtx->thread_, &Communication::threadCtx,
                     static_cast<void *>(communicationCtx));
}
