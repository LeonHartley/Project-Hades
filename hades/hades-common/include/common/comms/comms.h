#pragma once

#include <uv.h>
#include <string>
#include <cstdlib>
#include <memory>

#include <hiredis/hiredis.h>

#include <common/net/buffer.h>
#include <hiredis/async.h>
#include <iostream>
#include <map>
#include <common/util/lock.h>

namespace hades {
    class Communication;

    class CommunicationSubscriber {
    public:
        virtual void onMessage(Communication *ctx, short type, std::string id, std::unique_ptr<Buffer> msg) {

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
                : serviceName_(std::move(serviceName)),
                  subscriber_(std::move(subscriber)),
                  ctx_(redisAsyncConnect(redisConfig.host.c_str(), redisConfig.port)),
                  client_(redisAsyncConnect(redisConfig.host.c_str(), redisConfig.port)) {}

        ~Communication() {
            uv_thread_join(&this->thread_);
        }

        static void dispose();

        static void start(std::string serviceName, RedisConfig redisConfig,
                          std::unique_ptr<CommunicationSubscriber> subscriber);

        static void send(std::string serviceName, short type, std::string id, void (*writer)(Buffer *buf));

        std::map<std::string, long> *services() {
            return &services_;
        };

        RwMutex *servicesLock() {
            return &servicesLock_;
        }

        uv_loop_t *loop() {
            return &loop_;
        }

        redisAsyncContext *listenClient() {
            return ctx_;
        }

        redisAsyncContext *client() {
            return client_;
        }

        std::string serviceName() {
            return serviceName_;
        }

    private:
        std::string serviceName_;
        std::unique_ptr<CommunicationSubscriber> subscriber_;
        std::map<std::string, long> services_;

        redisAsyncContext *client_;
        redisAsyncContext *ctx_;

        uv_loop_t loop_;
        uv_thread_t thread_;
        RwMutex servicesLock_;

        static void threadCtx(void *ctx);

        static void createSubscription(redisAsyncContext *redis, void *r, void *ctx);

        void onServiceAvailable(std::string serviceName);

        void onMessage(redisReply *payload);
    };
}