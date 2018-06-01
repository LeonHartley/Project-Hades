#pragma once

#include <common/net/messages/message.h>
#include <string>

namespace hades {

    class MotdNotificationComposer : public Message {
    public:
        short getId() const override {
            return 408;
        }

        void compose(Buffer &buffer) override {
            buffer.write<std::string>("Yoo");
        }
    };
}