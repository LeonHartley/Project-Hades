#pragma once

#include <MySQLConnection.h>
#include <storage/repositories/players.h>

namespace hades {
    class StorageCtx {
        using ConnectionPool = active911::ConnectionPool<active911::MySQLConnection>;

    public:
        StorageCtx(std::shared_ptr<ConnectionPool> pool) : pool_(pool) {

        }

        std::shared_ptr<ConnectionPool> pool() {
            return pool_;
        }

        std::shared_ptr<PlayerRepository> players() {
            return playerRepository_;
        }


        static void setCtx(std::shared_ptr<StorageCtx> ctx) {
            ctx_ = ctx;
        }

        static std::shared_ptr<StorageCtx> getCtx() {
            return ctx_;
        }

    private:
        static std::shared_ptr<StorageCtx> ctx_;

        std::shared_ptr<PlayerRepository> playerRepository_;
        std::shared_ptr<ConnectionPool> pool_;

    };
}