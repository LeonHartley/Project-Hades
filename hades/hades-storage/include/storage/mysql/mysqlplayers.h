#pragma once

#include <storage/repositories/players.h>

namespace hades {
    class MySQLPlayerRepository : public PlayerRepository {
    public:
        virtual std::unique_ptr<PlayerData> getDataById(int id);
    };

}