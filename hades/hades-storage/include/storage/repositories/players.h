#pragma once

#include <storage/models/player.h>
#include <memory>

namespace hades {
    class PlayerRepository {
    public:
        virtual std::unique_ptr<PlayerData> getDataByTicket(std::string sso) = 0;

        virtual std::unique_ptr<PlayerData> getDataById(int id) = 0;
    };
}