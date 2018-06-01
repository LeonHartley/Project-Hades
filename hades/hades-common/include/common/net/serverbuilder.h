#pragma once

#include <memory>
#include "streamhandler.h"
#include "server.h"

namespace hades {
    class ServerBuilder {

    public:
        static std::unique_ptr<ServerBuilder> newBuilder() {
            return std::make_unique<ServerBuilder>();
        }

        ServerBuilder *streamHandler(StreamHandler clientHandler) {
            streamHandler_ = clientHandler;
            return this;
        }

        ServerBuilder *sessionFactory(SessionFactory sessionFactory) {
            sessionFactory_ = sessionFactory;
            return this;
        }

        ServerBuilder *uvLoop(uv_loop_t *loop) {
            loop_ = loop;
            return this;
        }

        ServerBuilder *host(std::string host) {
            host_ = std::move(host);
            return this;
        }

        ServerBuilder *port(short port) {
            port_ = port;
            return this;
        }

        std::unique_ptr<GameServer> create() {
            return std::make_unique<GameServer>(host_, port_, std::make_unique<SessionFactory>(sessionFactory_),
                                                std::make_unique<StreamHandler>(streamHandler_),
                                                loop_);
        }

    private:
        std::string host_ = "0.0.0.0";
        short port_ = 30000;

        uv_loop_t *loop_;

        StreamHandler streamHandler_;
        SessionFactory sessionFactory_;
    };
}