#pragma once

#include <uv.h>
#include <common/net/messages/message.h>
#include <vector>
#include <memory>
#include <mutex>
#include <storage/models/player.h>
#include <common/net/buffer.h>

namespace hades {
    class Session;

    static int counter = 0;

    class SessionContext {
    public:
        SessionContext() {

        }

        ~SessionContext() {

        }

        virtual void handleMessage(Session *session, std::unique_ptr<Buffer> buffer);
    };

    class Session {
    public:
        Session(uv_stream_t *handle, std::unique_ptr<SessionContext> ctx) : handle_(handle),
                                                                            context_(std::move(ctx)) {
        }

        ~Session() {
            this->context_ = nullptr;
        }

        void send(const Message &message);

        static Session *fromStream(uv_stream_t *stream) {
            return static_cast<Session *>(stream->data);
        }

        void close();

        void sendQueued(const Message &message);

        void flush();

        void context(std::unique_ptr<SessionContext> ctx) {
            context_ = std::move(ctx);
        }

        SessionContext *context() {
            return this->context_.get();
        }

    private:
        void flushBuffer(std::unique_ptr<Buffer> buffer);

        uv_stream_t *handle_;

//        std::mutex msgQueueLockm_;
//        std::unique_ptr<Buffer> buffer_;
        std::unique_ptr<SessionContext> context_;
    };
}