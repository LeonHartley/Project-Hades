//
// Created by Leon on 01/06/2018.
//

#include <storage/storagectx.h>
#include <common/log/log.h>

#include "MySQLConnection.h"

using namespace active911;

void hades::StorageCtx::test() {
    // Create a pool of 5 MySQL connections
    shared_ptr<MySQLConnectionFactory>mysql_connection_factory(new MySQLConnectionFactory("localhost","root","mysql_password"));
    shared_ptr<ConnectionPool<MySQLConnection> >mysql_pool(new ConnectionPool<MySQLConnection>(5, mysql_connection_factory));


}