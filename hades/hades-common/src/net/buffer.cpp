#include "common/net/buffer.h"

#include <string>

template<>
int hades::Buffer::read() {
    return (0xff & this->buffer_[this->readerIndex_++] << 24) |
           (0xff & this->buffer_[this->readerIndex_++] << 16) |
           (0xff & this->buffer_[this->readerIndex_++] << 8) |
           (0xff & this->buffer_[this->readerIndex_++]);
}

template<typename W>
void hades::Buffer::write(W data) {

}

template<>
short hades::Buffer::read() {
    return (0xff & this->buffer_[this->readerIndex_++]) << 8 |
           (0xff & this->buffer_[this->readerIndex_++] << 0);
}

template<>
std::string hades::Buffer::read() {
    short len = this->read<short>();

    return std::string(this->buffer_ + this->readerIndex_, static_cast<unsigned long>(this->readerIndex_ += len));
}

template<>
bool hades::Buffer::read() {
    return true;
}
