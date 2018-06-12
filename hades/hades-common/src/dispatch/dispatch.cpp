#include <common/dispatch/dispatch.h>

using namespace hades;

struct DispatchAsync {
    void *ctx;
    DispatchAsyncCallback cb;

};

//DispatchGroups::Game = std::make_shared<Dispatch>(4);
//DispatchGroups::Util = std::make_shared<Dispatch>(4);

static void asyncCallback(uv_async_t *handle) {
    if (handle->data != nullptr) {
        // do work
        auto async = static_cast<DispatchAsync *>(handle->data);

        async->cb(async->ctx);

        free(handle->data);
    }

    free(handle);
}

void DispatchLoop::start() {
    uv_loop_init(loop_);

    uv_thread_create(thread_, [](void *data) {
        auto dispatch = static_cast<DispatchLoop *>(data);

        auto *async = static_cast<uv_async_t *>(malloc(sizeof(uv_async_t)));
        async->data = nullptr;

        uv_async_init(dispatch->loop_, async, &asyncCallback);
        uv_async_send(async);

        int result = uv_run(dispatch->loop_, UV_RUN_DEFAULT);

        if (result) {
            // Handle error.
        }

    }, static_cast<void *>(this));
}

void DispatchLoop::async(DispatchAsyncCallback cb, void *ctx) {
    auto *handle = static_cast<uv_async_t *>(malloc(sizeof(uv_async_t)));
    auto *async = static_cast<DispatchAsync *>(malloc(sizeof(DispatchAsync)));

    async->ctx = ctx;
    async->cb = cb;

    handle->data = async;
    uv_async_init(loop_, handle, &asyncCallback);
    uv_async_send(handle);
}
