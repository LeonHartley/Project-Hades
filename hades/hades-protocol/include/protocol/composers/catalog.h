#pragma once

#include <common/net/messages/message.h>

namespace hades {
    class BuildersClubMembershipMessageComposer : public Message {
    public:
        BuildersClubMembershipMessageComposer() : Message() {

        }

        short getId() const override {
            return 2286;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(999999999);
            buffer->write<int>(100);
            buffer->write<int>(2);
        }
    };
}