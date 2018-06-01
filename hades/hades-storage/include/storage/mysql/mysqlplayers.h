#pragma once

#include <storage/storagectx.h>
#include <storage/repositories/players.h>

namespace hades {
    class MySQLPlayerRepository : public PlayerRepository {
    public:
        MySQLPlayerRepository(std::shared_ptr<StorageCtx> ctx) : ctx_(ctx) {
        }

        virtual std::unique_ptr<PlayerData> getDataById(int id);

    private:
        std::shared_ptr<StorageCtx> ctx_;
    };

}