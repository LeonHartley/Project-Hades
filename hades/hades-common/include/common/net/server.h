#pragma once

#include <string>

namespace hades {
    class TcpServer {

    public:
        TcpServer(const std::string host, short port) {
            this->host_ = host;
            this->port_ = port;
        }

    private:
        std::string host_;
        short port_;
    };
}
