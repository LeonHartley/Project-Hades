#pragma once

#include <uv.h>
#include <common/net/messages/message.h>
#include <vector>
#include <memory>
#include <mutex>
#include <storage/models/player.h>

namespace hades {
    class Session;

    class SessionContext {
    public:
        virtual void handleMessage(Session *session, std::unique_ptr<Buffer> buffer);
    };

    class Session {
    public:
        Session(uv_stream_t *handle) : handle_(handle), context_(std::make_unique<SessionContext>()) {
        }

        ~Session() {

        }

        void send(const Message &message);

        void send(std::vector<Message *> messages);

        static Session *fromStream(uv_stream_t *stream) {
            return reinterpret_cast<Session *>(stream->data);
        }

        void close();

        void sendQueued(const Message &message);

        void flush();

        void context(std::unique_ptr<SessionContext> ctx) {
            this->context_ = std::move(ctx);
        }

        SessionContext *context() {
            return this->context_.get();
        }

    private:
        void flushBuffer(std::unique_ptr<Buffer> buffer);

        uv_stream_t *handle_;

        std::mutex msgQueueLock_;
        std::unique_ptr<Buffer> buffer_;
        std::unique_ptr<SessionContext> context_;
    };
}