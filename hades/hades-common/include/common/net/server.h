#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "streamhandler.h"

namespace hades {
    class GameServer {

    public:
        GameServer(std::string &host, short port, std::unique_ptr<StreamHandler> streamHandler, uv_loop_t *loop) : host_(host),
                                                   port_(port), streamHandler_(streamHandler), loop_(loop) {
        }

        ~GameServer() {
            free(loop_);
        }

        void start();
    private:
        void createStream(uv_stream_t *server);

        const std::string host_;
        const short port_;

        uv_loop_t *loop_;
        const std::unique_ptr<StreamHandler> &streamHandler_;
    };
}
