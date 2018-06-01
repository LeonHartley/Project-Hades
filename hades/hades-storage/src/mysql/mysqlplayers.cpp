#include <storage/mysql/mysqlplayers.h>

using namespace hades;

std::unique_ptr<PlayerData> MySQLPlayerRepository::getDataById(int id) {
    return std::make_unique<PlayerData>(1, 7, "Leon", "", "", PlayerGender::MALE, true, 0, 0, 0, 0, 0, 0, 0, 0);
}