#pragma once

#include <malloc.h>

namespace hades {
    struct Buffer {

    public:
        Buffer(size_t size, bool expandable) {
            size_ = size;
            expandable_ = expandable;
            buffer_ = (char *) malloc(size);
            readerIndex_ = 0;
            writerIndex_ = 0;
        }

        Buffer(size_t size, char *buffer) : size_(size), buffer_(buffer) {
            size_ = size;
            expandable_ = false;
            readerIndex_ = 0;
            readerIndex_ = 0;
        }

        ~Buffer() {
            free(buffer_);
        }

        template<typename R>
        R read();

        template<typename W>
        void write(W data);

    private:
        char *buffer_;
        size_t size_;
        bool expandable_;

        int readerIndex_ = 0;
        int writerIndex_ = 0;
    };

}