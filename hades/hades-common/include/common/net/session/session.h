#pragma once

#include <uv.h>

namespace hades {
    class Session {
    public:
        Session(uv_stream_t *handle) : handle_(handle) {

        }

    private:
        const uv_stream_t *handle_;
    };
}