#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "streamhandler.h"

namespace hades {
    class GameServer {

    public:
        GameServer(std::string host, short port, std::unique_ptr<StreamHandler> streamHandler) : host_(std::move(host)),
                                                   port_(port), streamHandler_(streamHandler) {
        }

        void start() {
            /* start the server */

        }

    private:
        const std::string host_;
        const short port_;
        const std::unique_ptr<StreamHandler> &streamHandler_;
    };
}
