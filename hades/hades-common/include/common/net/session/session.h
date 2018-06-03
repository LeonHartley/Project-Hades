#pragma once

#include <uv.h>
#include <common/net/messages/message.h>
#include <vector>
#include <memory>
#include <mutex>


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

        void sendQueued(const Message &message);

        void flush();
    private:
        void flushBuffer(std::unique_ptr<Buffer> buffer);

        std::mutex msgQueueLock_;
        std::unique_ptr<Buffer> buffer_;
        uv_stream_t *handle_;
    };
}