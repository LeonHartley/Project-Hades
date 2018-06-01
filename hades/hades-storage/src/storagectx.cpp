//
// Created by Leon on 01/06/2018.
//

#include <storage/storagectx.h>
#include <common/log/log.h>

#include "MySQLConnection.h"

using namespace active911;
using namespace hades;

const auto log = LoggerProvider::get("StorageCtx");

void StorageCtx::test() {
    // register storage logger
    // Create a pool of 5 MySQL connections
    std::shared_ptr<MySQLConnectionFactory> mysql_connection_factory(
            new MySQLConnectionFactory("localhost", "root", ""));

    std::shared_ptr<ConnectionPool<MySQLConnection>> mysql_pool(
            new ConnectionPool<MySQLConnection>(5, mysql_connection_factory));

    auto connection = mysql_pool->borrow();

    connection->sql_connection->setSchema("cometsrv");
    log->info("yoo");
}