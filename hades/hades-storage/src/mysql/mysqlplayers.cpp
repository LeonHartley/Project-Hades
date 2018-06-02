#include <storage/mysql/mysqlplayers.h>

using namespace hades;

std::unique_ptr<PlayerData> MySQLPlayerRepository::getDataById(int id) {
    ConnectionGuard guard = this->ctx_->pool()->open();

    try {
        std::cout << "using connection here...\n";
        std::cout << "using connection here...\n";
        std::cout << "using connection here...\n";
        std::cout << "using connection here...\n";

        auto stmt = guard->prepareStatement("SELECT 1;");
    } catch (sql::SQLException exception) {
        // handle exception
    }

    return std::make_unique<PlayerData>(1, 7, "Leon", "", "", PlayerGender::MALE, true, 0, 0, 0, 0, 0, 0, 0, 0);
}