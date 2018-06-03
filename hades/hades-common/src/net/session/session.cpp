#include <common/net/session/session.h>

using namespace hades;

void writeComplete(uv_write_t *writer, int status) {
    free(writer->data);
    free(writer);
}

void Session::send(const Message &message) {
    // Create an expandable buffer that doesn't free the inner buffer
    auto *writer = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
    Buffer buf(256, true, false);

    buf.write<int>(0);
    buf.write<short>(message.getId());

    message.compose(buf);

    const uv_buf_t buffer = uv_buf_init(buf.prepare(), static_cast<unsigned int>(buf.writerIndex()));

    writer->handle = this->handle_;
    writer->data = buffer.base;

    uv_write(writer, this->handle_, &buffer, 1, &writeComplete);
}