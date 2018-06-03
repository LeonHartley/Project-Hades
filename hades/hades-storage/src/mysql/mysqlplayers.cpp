#include <storage/mysql/mysqlplayers.h>
#include <common/log/log.h>

using namespace hades;

const auto log = LoggerProvider::get("PlayerRepository");

std::unique_ptr<PlayerData> MySQLPlayerRepository::getDataById(int id) {
    ConnectionGuard guard = this->ctx_->pool()->open();

    try {
        auto stmt = guard->prepare("SELECT id, rank, username, motto, figure, gender, vip, credits, vip_points, "
                                   "activity_points, seasonal_points, reg_timestamp, last_online, favourite_group, quest_id "
                                   " FROM players WHERE id = ?;");

        stmt->setInt(1, id);

        auto result = guard->executeQuery(std::move(stmt));

        while (result->next()) {
            return this->playerDataFactory_.create(result->getInt("id"), result->getInt("rank"),
                                                   result->getString("username"), result->getString("motto"),
                                                   result->getString("figure"),
                                                   result->getString("gender") == "M" ? MALE : FEMALE,
                                                   result->getString("vip") == "1", result->getInt("credits"),
                                                   result->getInt("vip_points"), result->getInt("activity_points"),
                                                   result->getInt("seasonal_points"),
                                                   result->getInt("reg_timestamp"), result->getInt("last_online"),
                                                   result->getInt("favourite_group"), result->getInt("quest_id"));
        }
    } catch (sql::SQLException exception) {
        // handle exception
        log->error("Failed to player by ID: %v, error: %v", id, exception.getSQLState());
    }

    return nullptr;
}

std::unique_ptr<PlayerData> MySQLPlayerRepository::getDataByTicket(std::string sso) {
    ConnectionGuard guard = this->ctx_->pool()->open();

    try {
        auto stmt = guard->prepare("SELECT id, rank, username, motto, figure, gender, vip, credits, vip_points, "
                                   "activity_points, seasonal_points, reg_timestamp, last_online, favourite_group, quest_id "
                                   " FROM players WHERE auth_ticket = ?");

        stmt->setString(1, std::move(sso));

        auto result = guard->executeQuery(std::move(stmt));

        while (result->next()) {
            return this->playerDataFactory_.create(result->getInt("id"), result->getInt("rank"),
                                                   result->getString("username"), result->getString("motto"),
                                                   result->getString("figure"),
                                                   result->getString("gender") == "M" ? MALE : FEMALE,
                                                   result->getString("vip") == "1", result->getInt("credits"),
                                                   result->getInt("vip_points"), result->getInt("activity_points"),
                                                   result->getInt("seasonal_points"),
                                                   result->getInt("reg_timestamp"), result->getInt("last_online"),
                                                   result->getInt("favourite_group"), result->getInt("quest_id"));
        }
    } catch (sql::SQLException exception) {
        // handle exception
        log->error("Failed to player by auth ticket: %v, error: %v", sso, exception.getSQLState());
    }

    return nullptr;
}
