#pragma once

#include <string>
#include <utility>
#include <iostream>

#include "streamhandler.h"

namespace hades {
    class GameServer {

    public:
        GameServer(std::string &host, short port, std::unique_ptr<SessionFactory> sessionFactory, std::unique_ptr<StreamHandler> streamHandler, uv_loop_t *loop) : host_(host),
                                                   port_(port), sessionFactory_(std::move(sessionFactory)), streamHandler_(std::move(streamHandler)), loop_(loop) {
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

        const std::unique_ptr<SessionFactory> sessionFactory_;

        const std::unique_ptr<StreamHandler> streamHandler_;

        static void allocateUvBuffer(uv_stream_t *stream, size_t recommendedSize, uv_buf_t *out);

        static void onDataReceived(uv_stream_t *stream, size_t read, uv_buf_t *buffer);

        static void onStreamClosed(uv_handle_t *stream);
    };
}
