#include <iostream>
#include <memory>

#include <common/net/buffer.h>
#include <common/net/serverbuilder.h>
#include <common/log/log.h>

#include <storage/storagectx.h>
#include <storage/mysql/mysqlplayers.h>

INITIALIZE_EASYLOGGINGPP

using namespace active911;
using namespace hades;

void initialise_storage() {
    // Create a pool of 5 MySQL connections
    std::shared_ptr<MySQLConnectionFactory> mysql_connection_factory(
            new MySQLConnectionFactory("localhost", "root", ""));

    std::shared_ptr<ConnectionPool<MySQLConnection>> mysql_pool(
            new ConnectionPool<MySQLConnection>(5, mysql_connection_factory));

    auto storageCtx = std::make_shared<StorageCtx>(mysql_pool, std::make_shared<MySQLPlayerRepository>());
    StorageCtx::ctx(storageCtx);

    auto player = StorageCtx::players()->getDataById(1);

    LoggerProvider::get("main")->info("Player %v", player->getUsername());
}

void initialise_net() {
    uv_loop_t netLoop;
    uv_loop_init(&netLoop);

    std::unique_ptr<GameServer> gameServer = ServerBuilder::newBuilder()
            ->host("0.0.0.0")
            ->port(1234)
            ->streamHandler(StreamHandler())
            ->uvLoop(&netLoop)
            ->create();

    gameServer->start();
}

int main(int argc, char *argv[]) {
    initialise_storage();
    initialise_net();
}