#pragma once

#include <uv.h>
#include <common/net/messages/message.h>
#include <vector>
#include <memory>
#include <mutex>
#include <storage/models/player.h>
#include <common/net/buffer.h>
#include <atomic>
#include <map>

namespace hades {
    class Session;

    class SessionContext {
    public:
        SessionContext() {

        }

        ~SessionContext() {

        }

        virtual void handleMessage(Session *session, std::unique_ptr<Buffer> buffer);
    };

    static std::atomic<long> SESSION_COUNTER(0);

    class Session {
    public:
        Session(uv_stream_t *handle, std::unique_ptr<SessionContext> ctx) : id_(SESSION_COUNTER++), handle_(handle),
                                                                            context_(std::move(ctx)) {
        }

        ~Session() {
            this->context_ = nullptr;
            std::cout << "SESSION DISPOSED" << std::endl;
        }

        void send(const Message &message);

        static Session *fromStream(uv_stream_t *stream);

        static Session *fromId(long id);

        static void registerSession(long id, std::unique_ptr<Session> session);

        static void removeSession(long id);

        void close();

        void sendQueued(const Message &message);

        void flush();

        void context(std::unique_ptr<SessionContext> ctx) {
            context_ = std::move(ctx);
        }

        SessionContext *context() {
            return this->context_.get();
        }

        long &id() {
            return id_;
        }

    private:
        void flushBuffer(std::unique_ptr<Buffer> buffer);

        uv_stream_t *handle_;

        std::unique_ptr<SessionContext> context_;
//        std::mutex msgQueueLockm_;
//        std::unique_ptr<Buffer> buffer_;
        long id_;
    };
}