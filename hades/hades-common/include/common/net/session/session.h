#pragma once

#include <uv.h>
#include <common/net/messages/message.h>

namespace hades {
    class Session {
    public:
        Session(uv_stream_t *handle) : handle_(handle) {

        }

        void send(const Message &message) {

        }

        static Session *fromStream(uv_stream_t *stream) {
            return reinterpret_cast<Session *>(stream->data);
        }

    private:
        const uv_stream_t *handle_;
    };
}