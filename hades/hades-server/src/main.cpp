#include <iostream>
#include <memory>

#include <common/pool.h>
#include <common/log/log.h>
#include <common/net/buffer.h>
#include <common/net/session/sessionfactory.h>
#include <common/net/serverbuilder.h>

#include <storage/storagectx.h>
#include <storage/mysql/mysqlplayers.h>

#include <common/comms/comms.h>
#include <server/comms/serversubscriber.h>
#include <common/file.h>

#include <json/json.h>

INITIALIZE_EASYLOGGINGPP

using json = nlohmann::json;

auto const logger = hades::LoggerProvider::get("Boot");

namespace hades {
    struct DatabaseConfig {
        std::string host;
        std::string username;
        std::string password;
        std::string database;
        int poolSize;
    };

    struct ServerConfig {
        std::string host;
        short port;
    };

    void initialiseStorage(DatabaseConfig databaseConfig) {
        std::shared_ptr<ConnectionPool> pool =
                std::make_shared<ConnectionPool>(databaseConfig.poolSize, ConnectionFactory(
                        databaseConfig.host,
                        databaseConfig.username,
                        databaseConfig.password,
                        databaseConfig.database));

        StorageCtx::ctx(std::make_shared<StorageCtx>(std::move(pool)));
        StorageCtx::players(std::make_shared<MySQLPlayerRepository>(StorageCtx::ctx()));
    }

    void initialiseNet(ServerConfig serverConfig) {
        uv_loop_t netLoop;
        uv_loop_init(&netLoop);

        std::unique_ptr<GameServer> gameServer = ServerBuilder::newBuilder()
                ->host(serverConfig.host)
                ->port(serverConfig.port)
                ->sessionFactory(SessionFactory())
                ->streamHandler(StreamHandler())
                ->uvLoop(&netLoop)
                ->create();

        gameServer->start();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Missing configuration profile file path!" << std::endl;
        return 1;
    }

    const std::string configPath = argv[1];
    const std::string databaseConfigPath = argv[2];
    const std::string serviceProfilePath = argv[3];

    const auto config = json::parse(hades::File::load(configPath));
    const auto databaseConfig = json::parse(hades::File::load(databaseConfigPath))["mysql"];
    const auto serverProfile = json::parse(hades::File::load(serviceProfilePath));

    hades::Communication::start(serverProfile["service"]["name"], hades::RedisConfig{
            .host = config["comms"]["host"],
            .port = config["comms"]["port"],
    }, std::make_unique<hades::ServerSubscriber>());

    hades::initialiseStorage(hades::DatabaseConfig{
            .host = databaseConfig["host"],
            .username = databaseConfig["username"],
            .password = databaseConfig["password"],
            .database = databaseConfig["database"],
            .poolSize = databaseConfig["poolSize"]
    });

    hades::initialiseNet(hades::ServerConfig{
            .host = serverProfile["peer"]["host"],
            .port = serverProfile["peer"]["port"]
    });

    hades::Communication::dispose();
}