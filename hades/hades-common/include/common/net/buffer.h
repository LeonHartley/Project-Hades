#pragma once

#include <cstdlib>
#include <cstring>

namespace hades {
    class Buffer {

    public:
        Buffer(size_t size, bool expandable, bool freeOnDelete = true) {
            size_ = size;
            expandable_ = expandable;
            buffer_ = (char *) malloc(size);
            freeOnDelete_ = freeOnDelete;
        }

        Buffer(size_t size, const char *buffer, bool freeOnDelete = true) : size_(size), buffer_(
                const_cast<char *>(buffer)),
                                                                            freeOnDelete_(freeOnDelete) {
            expandable_ = false;
        }

        ~Buffer() {
            if (freeOnDelete_) {
                free(buffer_);
            }
        }

        bool hasData() {
            return this->readerIndex_ < this->size_;
        }

        int writerIndex() {
            return this->writerIndex_;
        }

        int readerIndex() {
            return this->readerIndex_;
        }

        int bytesRemaining() {
            return static_cast<int>(this->size_ - this->readerIndex_);
        }

        void copyFrom(size_t length, char *src) {
            memcpy(this->buffer_, src, length);
        }

        void copyTo(char *destination) {
            memcpy(destination, this->base(), static_cast<size_t>(this->writerIndex()));
        }

        void prepare(char *out);

        template<typename R>
        R read();

        template<typename W>
        void write(W data);

        template<typename W>
        void writeAt(W data, int index);

        char *base() {
            return this->buffer_;
        }

    private:
        char *buffer_;
        size_t size_;
        bool expandable_;
        bool freeOnDelete_;

        int readerIndex_ = 0;
        int writerIndex_ = 0;
    };

}