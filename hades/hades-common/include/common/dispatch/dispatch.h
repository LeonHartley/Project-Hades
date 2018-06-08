#pragma once

#include <uv.h>
#include <vector>
#include <mutex>
#include <memory>
#include <iostream>

namespace hades {

    class DispatchTimer {
    public:
        DispatchTimer(uv_loop_t *loop) : loop_(loop), timer_(static_cast<uv_timer_t *>(malloc(sizeof(uv_timer_t)))) {

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

        void start();

        template<typename T = void *>
                void async()
    private:
        uv_thread_t *thread_;
        uv_loop_t *loop_;
    };

    class Dispatch {

    public:
        Dispatch(int loopCount) : loopCount_(loopCount) {
            for (int i = 0; i < loopCount; i++) {
                loops_.push_back(std::make_unique<DispatchLoop>());
            }
        }

        void runAll() {
            for (auto &loop : loops_) {
                loop->start();
            }
        }

    private:
        std::mutex mutex_;
        std::vector<std::unique_ptr<DispatchLoop>> loops_;
        int loopCount_;
    };
}
