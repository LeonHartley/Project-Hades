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

        static std::shared_ptr<PlayerRepository> players() {
            return ctx()->playerRepository_;
        }

        static void players(std::shared_ptr<PlayerRepository> players) {
            ctx()->playerRepository_ = players;
        }

        static void ctx(std::shared_ptr<StorageCtx> ctx);

        static std::shared_ptr<StorageCtx> ctx();

    private:
        std::shared_ptr<PlayerRepository> playerRepository_;
        std::shared_ptr<ConnectionPool> pool_;
    };
}