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
            clientHandler_ = std::make_unique<StreamHandler>(clientHandler);

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
            return std::make_unique<GameServer>(host_, port_, std::move(clientHandler_));
        }

    private:
        std::string host_;
        short port_{};
        std::unique_ptr<StreamHandler> clientHandler_;
    };
}