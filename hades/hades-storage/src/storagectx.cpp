//
// Created by Leon on 01/06/2018.
//

#include <storage/storagectx.h>
#include <common/log/log.h>

#include <boost/shared_ptr.hpp>
#include "MySQLConnection.h"

using namespace active911;

void hades::StorageCtx::test() {
    // Create a pool of 5 MySQL connections
    std::shared_ptr<MySQLConnectionFactory> mysql_connection_factory(
            new MySQLConnectionFactory("localhost", "root", ""));

    std::shared_ptr<ConnectionPool<MySQLConnection>> mysql_pool(
            new ConnectionPool<MySQLConnection>(5, mysql_connection_factory));

    auto connection = mysql_pool->borrow();

    connection->sql_connection->setSchema("cometsrv");

}