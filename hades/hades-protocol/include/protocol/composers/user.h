#pragma once

#include <common/net/messages/message.h>

namespace hades {
    class FuserightsMessageComposer : public Message {

    public:
        explicit FuserightsMessageComposer(bool hasClub, int rank) : hasClub_(hasClub), rank_(rank) {

        }

        short getId() const override {
            return 1081;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(2);// clublevel ?
            buffer->write<int>(this->rank_);
            buffer->write<bool>(false);//ambassador
        };

    private:
        bool hasClub_;
        int rank_;

    };
}