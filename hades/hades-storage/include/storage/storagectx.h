#pragma once

#include <storage/repositories/players.h>
#include <storage/mysql/connectionpool.h>

namespace hades {
    class StorageCtx {
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