#pragma once

#include <common/net/messages/message.h>
#include <string>

namespace hades {
    class MotdNotificationMessageComposer : public Message {
    public:
        explicit MotdNotificationMessageComposer(std::string message) : message_(message) {

        }

        short getId() const override {
            return 408;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(1);
            buffer->write<std::string>(this->message_);
        }

    private:
        std::string message_;
    };

    class AuthenticationOKMessageComposer : public Message {
        short getId() const override {
            return 3054;
        }
    };
}