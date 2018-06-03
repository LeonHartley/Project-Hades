#include <common/net/session/session.h>
#include <iostream>
#include <common/log/log.h>
#include <common/net/server.h>

using namespace hades;

auto const log = LoggerProvider::get("Session");

void writeComplete(uv_write_t *writer, int status) {
    log->debug("write status: %v", status);

    free(writer->data);
    free(writer);
}

void Session::flushBuffer(Buffer buffer) {
    // Create an expandable buffer that doesn't free the inner buffer
    uv_write_t *writer = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
    const uv_buf_t buf = uv_buf_init(static_cast<char *>(malloc(static_cast<size_t>(buffer.writerIndex()))),
                                     static_cast<unsigned int>(buffer.writerIndex()));

    buffer.prepare(buf.base);

    writer->handle = this->handle_;
    writer->data = buf.base;

    log->debug("Writing data to client with length %v", buf.len, buf.base);

    uv_write(writer, this->handle_, &buf, 1, &writeComplete);
}

void Session::send(const Message &message) {
    Buffer buf(256, true, false);

    buf.write<short>(message.getId());
    message.compose(&buf);

    this->flushBuffer(std::move(buf));
}

void Session::send(std::vector<Message *> messages) {
    Buffer buf(256, true, false);

    std::for_each(messages.begin(), messages.end(), [&](Message *msg) {
        buf.write<short>(msg->getId());
        msg->compose(&buf);

        delete msg;
    });

    this->flushBuffer(std::move(buf));
}

void Session::close() {
    uv_close(reinterpret_cast<uv_handle_t *>(this->handle_), &GameServer::onStreamClosed);
}
