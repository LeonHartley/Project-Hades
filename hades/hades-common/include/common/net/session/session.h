#pragma once

#include <uv.h>
#include <common/net/messages/message.h>

namespace hades {
    class Session {
    public:
        Session(uv_stream_t *handle) : handle_(handle) {

        }

        void write(Message &message) {
            
        }

    private:
        const uv_stream_t *handle_;
    };
}