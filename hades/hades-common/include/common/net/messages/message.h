#pragma once

#include <common/net/buffer.h>

namespace hades {
    class Message {
    public:
        Message() = default;

        virtual short getId() const = 0;

        virtual void compose(Buffer &buffer) const {};
    };
}