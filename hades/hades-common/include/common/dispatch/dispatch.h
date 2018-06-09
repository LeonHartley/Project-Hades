#pragma once

#include <uv.h>
#include <vector>
#include <mutex>
#include <memory>
#include <iostream>
#include <dispatch/source.h>

namespace hades {
    typedef void (*DispatchAsyncCallback)(void *ctx);

    class DispatchTimer {
    public:
        DispatchTimer(uv_loop_t *loop) : loop_(loop), timer_(static_cast<uv_timer_t *>(malloc(sizeof(uv_timer_t)))) {
            uv_timer_start
        }

        ~DispatchTimer() {
            uv_timer_stop(timer_);
            free(timer_);
        }

    private:
        uv_loop_t *loop_;
        uv_timer_t *timer_;
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

        void async(DispatchAsyncCallback callback, void *arg) {
            nextLoop()->async(callback, arg);
        }

        std::unique_ptr<DispatchTimer> timer() {
            auto *loop = nextLoop();
            auto timer = std::make_unique<DispatchTimer>(loop->loop());
        };

    private:
        DispatchLoop *nextLoop() {
            int index = index_++;

            if (index >= loopCount_) {
                index_ = 0;
            }

            return loops_[index].get();
        }

        std::vector<std::unique_ptr<DispatchLoop>> loops_;
        std::atomic<int> index_;
        int loopCount_;
    };
}
