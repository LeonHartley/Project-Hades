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

    return std::string(this->buffer_ + this->readerIndex_, static_cast<unsigned long>(this->readerIndex_ += len));
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

    for(char &character : data) {
        this->write<char>(character);
    }
}
