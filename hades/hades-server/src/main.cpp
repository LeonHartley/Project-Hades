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
#include <storage/mysql/connectionpool.h>

#include <hiredis/hiredis.h>
#include <hiredis/adapters/libuv.h>

#include <common/comms/comms.h>

INITIALIZE_EASYLOGGINGPP

auto const logger = hades::LoggerProvider::get("Boot");

namespace hades {
//    class TestSubscriber : public CommunicationSubscriber {
//        void onMessage(Communication *ctx, short type, std::string id, std::uniqu
// e_ptr<Buffer> msg) override {
//            if(type == 1337) {
//                std::string payload = msg->read<std::string>();
//
//                logger->info("Received subscribed msg [%v] with data %v from %v", type, payload, id);
//            }
//
//            free(msg->base());
//        }
//    };

    void initialiseDispatch() {
        DispatchGroups::addGroup(RoomDispatch, std::make_unique<Dispatch>(3));
        DispatchGroups::addGroup(GameDispatch, std::make_unique<Dispatch>(3));

        DispatchGroups::group(RoomDispatch)->async<void>([](void *arg) {

        }, nullptr);
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
//    hades::Communication::start("peer-1", hades::RedisConfig{
//            .host = "localhost",
//            .port = 6379
//    }, std::make_unique<hades::TestSubscriber>(hades::TestSubscriber()));

    hades::initialiseDispatch();
    hades::initialiseStorage();
    hades::initialiseNet();


//    hades::Communication::dispose();

//    delete hades::DispatchGroups::Game;
//    delete hades::DispatchGroups::Util;
}