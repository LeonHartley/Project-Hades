#include <common/net/session/session.h>
#include <iostream>
#include <common/log/log.h>

using namespace hades;

auto const log = LoggerProvider::get("Session");

void writeComplete(uv_write_t *writer, int status) {
    log->debug("write status: %v", status);

    free(writer->data);
    free(writer);
}

void Session::send(const Message &message) {
    // Create an expandable buffer that doesn't free the inner buffer
    uv_write_t *writer = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
    Buffer buf(256, true, false);

    buf.write<short>(message.getId());
    message.compose(&buf);

    const uv_buf_t buffer = uv_buf_init(static_cast<char *>(malloc(static_cast<size_t>(buf.writerIndex()))),
                                        static_cast<unsigned int>(buf.writerIndex()));

    buf.prepare(buffer.base);

    writer->handle = this->handle_;
    writer->data = buffer.base;

    log->debug("Writing data to client with length %v, data %v", buffer.len, buffer.base);

    uv_write(writer, this->handle_, &buffer, 1, &writeComplete);
}