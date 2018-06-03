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

        virtual void compose(Buffer &buffer) const {
            buffer.write<int>(1);
            buffer.write<std::string>(this->message_);
        }

    private:
        std::string message_;
    };
}