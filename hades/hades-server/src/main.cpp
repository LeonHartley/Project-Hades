#include <iostream>
#include <memory>

#include <common/pool.h>
#include <common/log/log.h>
#include <common/net/buffer.h>
#include <common/net/session/sessionfactory.h>
#include <common/net/serverbuilder.h>

#include <storage/storagectx.h>
#include <storage/mysql/mysqlplayers.h>
#include <storage/mysql/connectionpool.h>

INITIALIZE_EASYLOGGINGPP

namespace hades {

    void testBuffer() {
        Buffer buf(512, true, false);

        buf.write<short>(412);
        buf.write<int>(1);
        buf.write<std::string>("Leon");

        char *a = static_cast<char *>(malloc(256));

        buf.prepare(a);

        free(buf.base());

        Buffer reader(static_cast<size_t>(buf.writerIndex()), a, false);

        std::cout << reader.read<int>() << " " << reader.read<short>() << " " << reader.read<int>() << " " << reader.read<std::string>() << "\n";
    }

    void initialiseStorage() {
        std::shared_ptr<ConnectionPool> pool =
                std::make_shared<ConnectionPool>(5, ConnectionFactory("localhost", "root", "", "cometsrv"));

        StorageCtx::ctx(std::make_shared<StorageCtx>(std::move(pool)));
        StorageCtx::players(std::make_shared<MySQLPlayerRepository>(StorageCtx::ctx()));

        auto player = StorageCtx::players()->getDataById(1);

        LoggerProvider::get("main")->info("Player %v", player->getUsername());
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
    hades::testBuffer();
    hades::initialiseStorage();
    hades::initialiseNet();
}