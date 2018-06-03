#pragma once

#include <common/net/buffer.h>
#include <iostream>

namespace hades {
    class Message {
    public:
        Message() {

        }

        ~Message() {

        }

        virtual short getId() const { return -1; };

        virtual void compose(Buffer *buffer) const {

        };
    };
}