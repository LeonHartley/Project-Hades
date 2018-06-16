#pragma once

#include <uv.h>
#include <vector>
#include <mutex>
#include <memory>
#include <iostream>
#include <atomic>
#include <map>
#include <common/util/lock.h>

#define RoomDispatch 0
#define GameDispatch 1
#define StorageDispatch 2

namespace hades {

    typedef void (*DispatchAsyncCallback)(void *ctx);

    class DispatchTimer {
    public:
        DispatchTimer(DispatchAsyncCallback callback, uv_loop_t *loop,
                      void *ctx, unsigned long initialDelay, unsigned long timeout) : initialDelay_(initialDelay),
                                                                                      timeout_(timeout),
                                                                                      callback_(callback),
                                                                                      ctx_(ctx),
                                                                                      timer_(static_cast<uv_timer_t *>(malloc(
                                                                                              sizeof(uv_timer_t)))) {
            uv_timer_init(loop, timer_);
            timer_->data = this;
        }

        void start() {
            uv_timer_start(timer_, &callback, initialDelay_, timeout_);
        }

        ~DispatchTimer() {
            uv_timer_stop(timer_);
            free(timer_);
        }

    private:
        static void callback(uv_timer_t *ctx) {
            auto timer = static_cast<DispatchTimer *>(ctx->data);

            timer->callback_(timer->ctx_);
        }

        uv_timer_t *timer_;
        void *ctx_;
        unsigned long initialDelay_;
        unsigned long timeout_;
        DispatchAsyncCallback callback_;
    };

    class DispatchLoop {

    public:
        DispatchLoop() : thread_(static_cast<uv_thread_t *>(malloc(sizeof(uv_thread_t)))),
                         loop_(static_cast<uv_loop_t *>(malloc(sizeof(uv_loop_t)))) {
            uv_loop_init(loop_);
        }

        ~DispatchLoop() {
            uv_stop(loop_);
            uv_thread_join(thread_);

            free(thread_);
            free(loop_);
        }

        void async(DispatchAsyncCallback callback, void *arg);

        void start();

        uv_loop_t *loop() {
            return loop_;
        }

    private:
        uv_thread_t *thread_;
        uv_loop_t *loop_;
    };

    class Dispatch {

    public:
        Dispatch(int loopCount) : loopCount_(loopCount), index_(0) {
            for (int i = 0; i < loopCount; i++) {
                loops_.push_back(std::make_unique<DispatchLoop>());
            }
        }

        void runAll() {
            for (auto &loop : loops_) {
                loop->start();
            }
        }

        template<typename Ctx>
        void async(void(*callback)(Ctx *), Ctx *arg) {
            nextLoop()->async(reinterpret_cast<DispatchAsyncCallback>(callback), static_cast<void *>(arg));
        }

        template<typename Ctx>
        std::unique_ptr<DispatchTimer> timer(void(*callback)(Ctx *), unsigned long initialDelay,
                                             unsigned long timeout, Ctx *data);

    private:
        DispatchLoop *nextLoop() {
            int index = index_++;

            if (index >= loopCount_) {
                index_, index = 0;
            }

            return loops_[index].get();
        }

        std::vector<std::unique_ptr<DispatchLoop>> loops_;
        std::atomic<int> index_;
        int loopCount_;
    };

    class DispatchGroups {
    public:
        static Dispatch *group(int id) {
            RwLockGuard lock(&mutex_, READ);

            if (dispatchGroups_.count(id)) {
                return dispatchGroups_.find(id)->second.get();
            }
        }

        static void addGroup(int id, std::unique_ptr<Dispatch> group) {
            RwLockGuard lock(&mutex_, WRITE);

            dispatchGroups_.emplace(id, std::move(group));
        }

    private:
        static RwMutex mutex_;
        static std::map<int, std::unique_ptr<Dispatch>> dispatchGroups_;
    };
}
