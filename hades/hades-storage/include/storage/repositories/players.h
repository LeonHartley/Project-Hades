#pragma once

#include <storage/models/player.h>
#include <memory>

namespace hades {
    class PlayerRepository {
    public:
        virtual std::unique_ptr<PlayerData> getDataById(int id) = 0;
    };
}