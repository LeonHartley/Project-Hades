#pragma once

#include <common/net/buffer.h>

namespace hades {
    class Message {
    public:
        Message() {

        }

        virtual void compose(Buffer &buffer) {

        }
    };
}