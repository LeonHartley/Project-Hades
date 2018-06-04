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

#include <hiredis/hiredis.h>
#include <hiredis/adapters/libuv.h>

#include <common/comms.h>

INITIALIZE_EASYLOGGINGPP


auto const log = hades::LoggerProvider::get("Boot");

namespace hades {
    class TestSubscriber : public CommunicationSubscriber {
        void onMessage(Communication *ctx, int type, std::string id, std::unique_ptr<Buffer> msg) override {
            log->info("Received subscribed msg with data %v, %v", type, id);

            free(msg->base());
        }
    };

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
    hades::Communication::start("peer-1", hades::RedisConfig{
            .host = "localhost",
            .port = 6379
    }, std::make_unique<hades::TestSubscriber>(hades::TestSubscriber()));

    std::unique_ptr<hades::Buffer> buf = std::make_unique<hades::Buffer>(256, false);

    buf->write<int>(1337);
    buf->write<std::string>("Leon's msg");
    buf->write<std::string>("herro");

    hades::Communication::send("peer-1", std::move(buf));

    hades::initialiseStorage();
    hades::initialiseNet();

    hades::Communication::dispose();
}