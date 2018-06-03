#pragma once

#include <uv.h>
#include <common/net/messages/message.h>
#include <vector>
#include <memory>


namespace hades {
    class Session {
    public:
        Session(uv_stream_t *handle) : handle_(handle) {

        }

        void send(const Message &message);

        void send(std::vector<Message *> messages);

        static Session *fromStream(uv_stream_t *stream) {
            return reinterpret_cast<Session *>(stream->data);
        }

        void close();

    private:
        void flushBuffer(Buffer buffer);

        uv_stream_t *handle_;
    };
}