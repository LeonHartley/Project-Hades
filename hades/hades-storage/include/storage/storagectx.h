#pragma once

#include <MySQLConnection.h>

namespace hades {
    class StorageCtx {

    public:
        static void initialise();

    private:
        std::shared_ptr<active911::ConnectionPool<active911::MySQLConnection>> pool_;
    };
}