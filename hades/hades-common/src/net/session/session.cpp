#include <common/net/session/session.h>
#include <iostream>
#include <common/log/log.h>
#include <common/net/server.h>
#include <map>

using namespace hades;

auto const logger = LoggerProvider::get("Session");

void writeComplete(uv_write_t *writer, int status) {
    logger->debug("write status: %v", status);

    free(writer->data);
    free(writer);
}

void Session::flushBuffer(std::unique_ptr<Buffer> buffer) {
    // Create an expandable buffer that doesn't free the inner buffer
    uv_write_t *writer = static_cast<uv_write_t *>(malloc(sizeof(uv_write_t)));
    const uv_buf_t buf = uv_buf_init(static_cast<char *>(malloc(static_cast<size_t>(buffer->writerIndex()))),
                                     static_cast<unsigned int>(buffer->writerIndex()));

    memcpy(buf.base, buffer->base(), static_cast<size_t>(buffer->writerIndex()));

    writer->handle = this->handle_;
    writer->data = buf.base;

    uv_write(writer, this->handle_, &buf, 1, &writeComplete);
    free(buffer->base());
//    this->buffer_ = nullptr;
}

void Session::send(const Message &message) {
    Buffer buf(256, true, false);

    buf.write<int>(0);
    buf.write<short>(message.getId());
    message.compose(&buf);
    buf.writeAt<int>(buf.writerIndex() - 4, 0);

    this->flushBuffer(std::make_unique<Buffer>(std::move(buf)));
}

void Session::sendQueued(const Message &message) {
//    std::lock_guard<std::mutex> guard(this->msgQueueLock_);
//
//    if(this->buffer_ == nullptr) {
//        this->buffer_ = std::make_unique<Buffer>(256, true);
//    }
//
//    int currentIndex = this->buffer_->writerIndex();
//
//    this->buffer_->write<int>(0);
//    this->buffer_->write<short>(message.getId());
//
//    message.compose(this->buffer_.get());
//
//    this->buffer_->writeAt<int>(this->buffer_->writerIndex() - 4, currentIndex);
}

void Session::flush() {
//    std::lock_guard<std::mutex> guard(this->msgQueueLock_);
//    this->flushBuffer(std::move(this->buffer_));
//    this->buffer_ = nullptr;
}


void Session::close() {
    uv_close(reinterpret_cast<uv_handle_t *>(this->handle_), &GameServer::onStreamClosed);
}

Session *Session::fromStream(uv_stream_t *stream) {
    return static_cast<Session *>(stream->data);
}

static std::mutex sessionsMutex_;
static std::map<long, std::unique_ptr<Session>> sessions_;

Session *Session::fromId(long id) {
    std::lock_guard<std::mutex> lock(sessionsMutex_);

    auto found = &sessions_.find(id)->second;

    if(found != nullptr) {
        return found->get();
    }

    return nullptr;
}

void Session::registerSession(long id, std::unique_ptr<Session> session) {
    std::lock_guard<std::mutex> lock(sessionsMutex_);

    sessions_.emplace(id, std::move(session));
}

void Session::removeSession(long id) {
    std::lock_guard<std::mutex> lock(sessionsMutex_);

    sessions_.erase(id);
}

void SessionContext::handleMessage(Session *session, std::unique_ptr<Buffer> buffer) {
    MessageDispatch::dispatch(session, std::move(buffer));
}
