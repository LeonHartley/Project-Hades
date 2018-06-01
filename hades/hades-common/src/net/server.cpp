#include <common/net/server.h>

using namespace hades;
void GameServer::createStream(uv_stream_t *serverStream) {
    // when we've created the stream, we pass it to
    //this->streamHandler_->onConnectionOpen(stream);
}

void GameServer::start() {
    uv_tcp_t server;
    sockaddr_in bind_addr;

    server.data = static_cast<void *>(this);

    uv_tcp_init(this->loop_, &server);
    uv_ip4_addr(this->host_.c_str(), this->port_, &bind_addr);
    uv_tcp_bind(&server, (const struct sockaddr *) &bind_addr, 0);

    auto acceptProxy = [](uv_stream_t *handle, int status) {
        auto gameServer = static_cast<GameServer *>(handle->data);

        gameServer->createStream(handle);
    };

    uv_listen((uv_stream_t *) &server, 128, acceptProxy);

    int result = uv_run(this->loop_, UV_RUN_DEFAULT);

    if (result) {
        /* Failed!*/
    }

    uv_loop_close(this->loop_);
    free(this->loop_);
}
