#pragma once

#include <algorithm>
#include <common/net/messages/message.h>
#include <storage/models/player.h>

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

    class UserObjectMessageComposer : public Message {

    public:
        UserObjectMessageComposer(PlayerData *playerData) : playerData_(playerData) {

        }

        short getId() const override {
            return 1513;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(playerData_->getId());
            buffer->write<std::string>(playerData_->getUsername());
            buffer->write<std::string>(playerData_->getFigure());
            buffer->write<std::string>(playerData_->getGender() == MALE ? "M" : "F");
            buffer->write<std::string>(playerData_->getMotto());

            std::string username = playerData_->getUsername();

            transform(username.begin(), username.end(), username.begin(), ::tolower);

            buffer->write<std::string>(std::move(username));
            buffer->write<bool>(true);
            buffer->write<int>(8);
            buffer->write<int>(3);//resp
            buffer->write<int>(3);//resp
            buffer->write<bool>(true);
            buffer->write<std::string>("");
            buffer->write<bool>(false);
            buffer->write<bool>(false);
        }

    private:
        PlayerData *playerData_;
    };

    class AllowancesMessageComposer : public Message {
    public:
        AllowancesMessageComposer() : Message() {

        }

        short getId() const override {
            return 3189;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(0); // Count
            buffer->write<std::string>("USE_GUIDE_TOOL");
            buffer->write<std::string>("");
            buffer->write<bool>(false);
            buffer->write<std::string>("GIVE_GUIdE_TOURS");
            buffer->write<std::string>("requirement.unfulfilled.helper_le");
            buffer->write<bool>(false);
            buffer->write<std::string>("JUDGE_CHAT_REVIEWS");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("VOTE_IN_COMPETITIONS");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("CALL_ON_HELPERS");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(false);
            buffer->write<std::string>("CITIZEN");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("TRADE");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("HEIGHTMAP_EDITOR_BETA");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(false);
            buffer->write<std::string>("EXPERIMENTAL_CHAT_BETA");
            buffer->write<std::string>("requirement.unfulfilled.helper_level_2");
            buffer->write<bool>(true);
            buffer->write<std::string>("EXPERIMENTAL_TOOLBAR");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("BUILDER_AT_WORK");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("NAVIGATOR_PHASE_ONE_2014");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(false);
            buffer->write<std::string>("CAMERA");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("NAVIGATOR_PHASE_TWO_2014");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("MOUSE_ZOOM");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
            buffer->write<std::string>("NAVIGATOR_ROOM_THUMBNAIL_CAMERA");
            buffer->write<std::string>(""); // ??
            buffer->write<bool>(true);
        }
    };

    class FavouriteRoomsMessageComposer : public Message {
    public:
        FavouriteRoomsMessageComposer() : Message() {

        }

        short getId() const override {
            return 2753;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(25);
            buffer->write<int>(0);
        }
    };

    class HomeRoomMessageComposer : public Message {
    public:
        HomeRoomMessageComposer() : Message() {

        }

        short getId() const override {
            return 1776;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(0);
            buffer->write<int>(0);
        }
    };
};