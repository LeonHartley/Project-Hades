#include <storage/mysql/connectionpool.h>

using namespace hades;

ConnectionGuard hades::ConnectionPool::open() {
    return ConnectionGuard(this->pop(), this);
}
