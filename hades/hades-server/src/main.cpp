#include <iostream>
#include <memory>

#include <common/pool.h>
#include <common/log/log.h>
#include <common/net/buffer.h>
#include <common/net/session/sessionfactory.h>
#include <common/net/serverbuilder.h>
#include <common/dispatch/dispatch.h>

#include <storage/storagectx.h>
#include <storage/mysql/mysqlplayers.h>

#include <common/comms/comms.h>
#include <server/comms/serversubscriber.h>

INITIALIZE_EASYLOGGINGPP

auto const logger = hades::LoggerProvider::get("Boot");

namespace hades {
    void initialiseDispatch() {
        DispatchGroups::addGroup(RoomDispatch, std::make_unique<Dispatch>(2));
        DispatchGroups::addGroup(GameDispatch, std::make_unique<Dispatch>(2));
    }

    void initialiseStorage() {
        std::shared_ptr<ConnectionPool> pool =
                std::make_shared<ConnectionPool>(5, ConnectionFactory("localhost", "root", "", "cometsrv"));

        StorageCtx::ctx(std::make_shared<StorageCtx>(std::move(pool)));
        StorageCtx::players(std::make_shared<MySQLPlayerRepository>(StorageCtx::ctx()));
    }

    void initialiseNet() {
        uv_loop_t netLoop;
        uv_loop_init(&netLoop);

        std::unique_ptr<GameServer> gameServer = ServerBuilder::newBuilder()
                ->host("0.0.0.0")
                ->port(30000)
                ->sessionFactory(SessionFactory())
                ->streamHandler(StreamHandler())
                ->uvLoop(&netLoop)
                ->create();

        gameServer->start();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Missing configuration profile file path!" << std::endl;
        return 1;
    }

    std::string databaseConfigPath = argv[1];
    std::string configProfilePath = argv[2];

    hades::Communication::start("peer-1", hades::RedisConfig{
            .host = "localhost",
            .port = 6379
    }, std::make_unique<hades::ServerSubscriber>());

    hades::initialiseDispatch();
    hades::initialiseStorage();
    hades::initialiseNet();

    hades::Communication::dispose();
}