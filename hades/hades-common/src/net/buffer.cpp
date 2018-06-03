#include "common/net/buffer.h"

#include <string>
#include <iostream>

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
    std::string str;

    for (int i = 0; i < len; i++) {
        str.append(1, this->buffer_[this->readerIndex_++]);
    }

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

template<>
void Buffer::writeAt(int data, int index) {
    this->buffer_[index++] = ((data >> 24) & 0xff);
    this->buffer_[index++] = ((data >> 16) & 0xff);
    this->buffer_[index++] = ((data >> 8) & 0xff);
    this->buffer_[index] = (data & 0xff);
}

template<>
void Buffer::write(bool data) {
    this->write<char>(data ? (char) 1 : (char) 0);
}

void Buffer::prepare(char *out) {
//    this->writeAt<int>(((int) this->writerIndex_ - 4), 0);

}

template<typename W>
void Buffer::write(W data) {
}

template<typename W>
void Buffer::writeAt(W data, int index) {

}
