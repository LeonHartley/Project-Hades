#include <iostream>
#include <memory>

#include <common/net/buffer.h>
#include <common/net/serverbuilder.h>
#include <common/log/log.h>

#include <storage/storagectx.h>
#include <storage/mysql/mysqlplayers.h>

INITIALIZE_EASYLOGGINGPP

using namespace active911;

namespace hades {
    void initialiseStorage() {
        // Create a pool of 5 MySQL connections
        std::shared_ptr<MySQLConnectionFactory> mysqlConnectionFactory(
                new MySQLConnectionFactory("localhost", "root", ""));

        std::shared_ptr<ConnectionPool<MySQLConnection>> mysqlPool(
                new ConnectionPool<MySQLConnection>(5, mysqlConnectionFactory));

        auto storageCtx = std::make_shared<StorageCtx>(mysqlPool);
        StorageCtx::ctx(std::move(storageCtx));

        // Setup repositories
        StorageCtx::players(std::make_shared<MySQLPlayerRepository>(StorageCtx::ctx()));

        auto player = StorageCtx::players()->getDataById(1);

        LoggerProvider::get("main")->info("Player %v", player->getUsername());
    }

    void initialiseNet() {
        uv_loop_t netLoop;
        uv_loop_init(&netLoop);

        std::unique_ptr<GameServer> gameServer = ServerBuilder::newBuilder()
                ->host("0.0.0.0")
                ->port(1234)
                ->sessionFactory(SessionFactory())
                ->streamHandler(StreamHandler())
                ->uvLoop(&netLoop)
                ->create();

        gameServer->start();
    }
}

int main(int argc, char *argv[]) {
    hades::initialiseStorage();
    hades::initialiseNet();
}