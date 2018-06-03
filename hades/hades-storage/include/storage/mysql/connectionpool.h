#pragma once

#include <common/pool.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/driver.h>

namespace hades {
    class Connection {

    public:
        Connection(std::shared_ptr<sql::Connection> connection) : connection_(connection) {}

        std::unique_ptr<sql::PreparedStatement> prepare(std::string query) {
            return std::unique_ptr<sql::PreparedStatement>(this->connection_->prepareStatement(query));
        }

        std::shared_ptr<sql::ResultSet> executeQuery(std::unique_ptr<sql::PreparedStatement> statement) {
            return std::shared_ptr<sql::ResultSet>(statement->executeQuery());
        }

        std::shared_ptr<sql::Connection> &get() {
            return connection_;
        }

        sql::Connection *operator->() const {
            return connection_.get();
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

        virtual std::shared_ptr<Connection> create() {
            sql::Driver *driver = get_driver_instance();
            sql::Connection *connection = driver->connect(this->host_, this->username_, this->password_);
            std::shared_ptr<sql::Connection> con(connection);

            connection->setSchema(this->schema_);

            return std::make_shared<Connection>(std::move(con));
        }

    private:
        std::string host_;
        std::string username_;
        std::string password_;
        std::string schema_;
    };

    typedef class ConnectionGuard;

    class ConnectionPool : public ObjectPool<Connection, ConnectionFactory> {
    public:
        ConnectionPool(int initialSize, const ConnectionFactory &factory) : ObjectPool(initialSize, factory) {

        }

        ConnectionGuard open();
    };

    class ConnectionGuard {
    public:
        ConnectionGuard(std::shared_ptr<Connection> con, ConnectionPool *pool) : obj_(std::move(con)),
                                                                                 pool_(pool) {}

        ~ConnectionGuard() {
            pool_->push(std::move(this->obj_));

            std::cout << "returnin obj to pool\n";
        }

//        Connection &connection() {
//            return obj_->get();
//        }

        Connection *operator->() const {
            return obj_.get();
        }

    private:
        const std::shared_ptr<Connection> obj_;
        ConnectionPool *pool_;
    };

}