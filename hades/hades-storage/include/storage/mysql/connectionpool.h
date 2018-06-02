#pragma once

#include <common/pool.h>
#include <cppconn/connection.h>
#include <cppconn/driver.h>

namespace hades {
    class Connection {

    public:
        Connection(std::shared_ptr<sql::Connection> connection) : connection_(connection) {}

        std::shared_ptr<sql::Connection> get() {
            return connection_;
        }

    private:
        std::shared_ptr<sql::Connection> connection_;
    };

    class ConnectionFactory : public ObjectPoolFactory<Connection> {

    public:
        ConnectionFactory(const std::string &host_, const std::string &username_,
                          const std::string &password_, const std::string &schema_) : host_(host_),
                                                                                      username_(username_),
                                                                                      password_(password_),
                                                                                      schema_(schema_) {}

        virtual std::unique_ptr<Connection> create() {
            sql::Driver *driver = get_driver_instance();
            sql::Connection *connection = driver->connect(this->host_, this->username_, this->password_);
            std::shared_ptr<sql::Connection> con(connection);

            connection->setSchema(this->schema_);

            return std::make_unique<Connection>(std::move(con));
        }

    private:
        std::string host_;
        std::string username_;
        std::string password_;
        std::string schema_;
    };

    class ConnectionPool : public ObjectPool<Connection, ConnectionFactory> {
    public:
        ConnectionPool(int initialSize, const ConnectionFactory &factory) : ObjectPool(initialSize, factory) {

        }
    };

}