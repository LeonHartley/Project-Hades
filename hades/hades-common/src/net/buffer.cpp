#include "common/net/buffer.h"

#include <string>

using namespace hades;

template<>
int Buffer::read() {
    return (0xff & this->buffer_[this->readerIndex_++] << 24) |
           (0xff & this->buffer_[this->readerIndex_++] << 16) |
           (0xff & this->buffer_[this->readerIndex_++] << 8) |
           (0xff & this->buffer_[this->readerIndex_++]);
}

template<>
short Buffer::read() {
    return (0xff & this->buffer_[this->readerIndex_++]) << 8 |
           (0xff & this->buffer_[this->readerIndex_++] << 0);
}

template<>
std::string Buffer::read() {
    short len = this->read<short>();
    auto str = std::string(this->buffer_ + this->readerIndex_, static_cast<unsigned long>(this->readerIndex_ + (len)));

    this->readerIndex_ += len;

    return std::move(str);
}

template<>
bool Buffer::read() {
    return true;
}

template<>
void Buffer::write(char data) {
    this->buffer_[this->writerIndex_++] = data;
}

template<>
void Buffer::write(short data) {
    this->buffer_[this->writerIndex_++] = ((data >> 8) & 0xff);
    this->buffer_[this->writerIndex_++] = (data & 0xff);
}

template<>
void Buffer::write(int data) {
    this->buffer_[this->writerIndex_++] = ((data >> 24) & 0xff);
    this->buffer_[this->writerIndex_++] = ((data >> 16) & 0xff);
    this->buffer_[this->writerIndex_++] = ((data >> 8) & 0xff);
    this->buffer_[this->writerIndex_++] = (data & 0xff);
}

template<>
void Buffer::write(std::string data) {
    this->write<short>(static_cast<short>(data.length()));

    for (char &character : data) {
        this->write<char>(character);
    }
}

char *Buffer::prepare() {
    size_t length = static_cast<size_t>(this->writerIndex_);
    char *buf = static_cast<char *>(malloc(length));

    this->writerIndex_ = 0;
    this->write<int>(static_cast<int>(length));

    memcpy(buf, this->buffer_, length);

    this->writerIndex_ = (int) length;
    return buf;
}
