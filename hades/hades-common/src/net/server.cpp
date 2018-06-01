#include <common/net/server.h>
#include <common/log/log.h>

using namespace hades;

auto const log = LoggerProvider::get("GameServer");
const char policyFile[208] = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy \ SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";

void GameServer::allocateUvBuffer(uv_stream_t *stream, size_t recommendedSize, uv_buf_t *out) {
    out->base = static_cast<char *>(malloc(recommendedSize));
    out->len = recommendedSize;
}

void GameServer::onDataReceived(uv_stream_t *stream, size_t read, uv_buf_t *buffer) {
    auto server = static_cast<GameServer *>(stream->loop->data);
    auto session = Session::fromStream(stream);

    if (read == UV_EOF) {
        uv_close((uv_handle_t *) stream, reinterpret_cast<uv_close_cb>(&GameServer::onStreamClosed));
        return;
    }

    if (buffer->base[0] == '<') {
        uv_write_t *req = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
        uv_buf_t buffer = uv_buf_init(static_cast<char *>(malloc(sizeof(policyFile))), sizeof(policyFile));

        buffer.base = (char *) policyFile;

        req->handle = stream;
        req->data = buffer.base;

        uv_write(req, stream, &buffer, 1, [](uv_write_t *req, int status) {
            uv_close(reinterpret_cast<uv_handle_t *>(req->handle), &GameServer::onStreamClosed);
        });
    } else {
        server->streamHandler_->onReceiveData(session, std::make_unique<Buffer>(buffer->len, buffer->base));
    }
}

void GameServer::onStreamClosed(uv_handle_t *stream) {
    auto server = reinterpret_cast<GameServer *>(stream->loop->data);
    auto session = Session::fromStream(reinterpret_cast<uv_stream_t *>(stream->data));

    log->debug("Stream closed");

    server->streamHandler_->onConnectionClosed(session);
    server->sessionFactory_->disposeSession(session);

    stream->data = nullptr;
}

void GameServer::createStream(uv_stream_t *serverStream) {
    auto server = reinterpret_cast<GameServer *>(serverStream->data);

    uv_tcp_t *client = (uv_tcp_t *) malloc(sizeof(uv_tcp_t));
    uv_stream_t *stream = (uv_stream_t *) client;
    Session *session = server->sessionFactory_->createSession(stream);

    uv_tcp_init(serverStream->loop, client);

    client->data = reinterpret_cast<void *>(session);
    server->streamHandler_->onConnectionOpen(Session::fromStream(stream));

    int result = uv_accept(serverStream, stream);

    if (result == 0) {
        log->trace("Starting read for stream");

        uv_read_start(stream,
                      reinterpret_cast<uv_alloc_cb>(&GameServer::allocateUvBuffer),
                      reinterpret_cast<uv_read_cb>(&GameServer::onDataReceived));

    } else {
        log->debug("Failed to accept client, err: %v", uv_err_name(result));
    }
}

void GameServer::start() {
    uv_tcp_t server;
    sockaddr_in bind_addr;

    server.data = static_cast<void *>(this);
    this->loop_->data = static_cast<void *>(this);

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
