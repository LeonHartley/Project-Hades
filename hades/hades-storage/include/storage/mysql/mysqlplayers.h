#pragma once

#include <storage/storagectx.h>
#include <storage/repositories/players.h>

namespace hades {
    class MySQLPlayerRepository : public PlayerRepository {
    public:
        MySQLPlayerRepository(std::shared_ptr<StorageCtx> ctx) : ctx_(ctx) {
        }

        virtual std::unique_ptr<PlayerData> getDataByTicket(std::string sso);

        virtual std::unique_ptr<PlayerData> getDataById(int id);
    private:
        PlayerDataFactory playerDataFactory_;
        std::shared_ptr<StorageCtx> ctx_;
    };

}