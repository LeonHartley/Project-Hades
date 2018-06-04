#pragma once

#include <uv.h>
#include <string>
#include <cstdlib>
#include <memory>

#include <hiredis/hiredis.h>

#include <common/net/buffer.h>
#include <hiredis/async.h>
#include <iostream>

namespace hades {
    class Communication;

    class CommunicationSubscriber {
    public:
        virtual void onMessage(Communication *ctx, int type, std::string id, std::unique_ptr<Buffer> msg) {
            std::cout << "Hmmm" << std::endl;
        };
    };

    struct RedisConfig {
        std::string host;
        int port;

        // probably other stuff here down the line, like pw etc...
    };

    class Communication {
    public:
        Communication(std::string serviceName, RedisConfig redisConfig,
                      std::unique_ptr<CommunicationSubscriber> subscriber)
                : serviceName_(serviceName),
                  subscriber_(std::move(subscriber)),
                  thread_(static_cast<uv_thread_t *>(
                                  malloc(sizeof(uv_thread_t)))),

                  loop_(static_cast<uv_loop_t *>(malloc(
                          sizeof(uv_loop_t)))),
                  ctx_(redisAsyncConnect(redisConfig.host.c_str(), redisConfig.port)) {}

        ~Communication() {
            uv_thread_join(this->thread_);

            free(this->thread_);
            free(this->loop_);
        }

        static void dispose();

        static void start(std::string serviceName, RedisConfig redisConfig, std::unique_ptr<CommunicationSubscriber> subscriber);

        uv_loop_t *loop() {
            return loop_;
        }

        redisAsyncContext *redis() {
            return ctx_;
        }

    private:
        std::string &serviceName_;
        std::unique_ptr<CommunicationSubscriber> subscriber_;

        redisAsyncContext *ctx_;
        uv_loop_t *loop_;
        uv_thread_t *thread_;

        static void threadCtx(void *ctx);
    };
}