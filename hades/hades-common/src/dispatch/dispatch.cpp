#include <common/dispatch/dispatch.h>

static void asyncCallback(uv_async_t *handle) {
    if (handle->data != NULL) {
        // do work
    }

    free(handle);
}

void hades::DispatchLoop::start() {
    uv_loop_init(loop_);

    uv_thread_create(thread_, [](void *data) {
        auto dispatch = static_cast<DispatchLoop *>(data);

        uv_async_t *async = static_cast<uv_async_t *>(malloc(sizeof(uv_async_t)));
        async->data = NULL;

        uv_async_init(dispatch->loop_, async, &asyncCallback);
        uv_async_send(async);

        int result = uv_run(dispatch->loop_, UV_RUN_DEFAULT);

        if (result) {
            // Handle error.
        }

    }, static_cast<void *>(this));
}
