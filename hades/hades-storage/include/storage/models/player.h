#pragma once

#include <memory>
#include <string>

namespace hades {
    enum PlayerGender {
        MALE, FEMALE
    };

    class PlayerData {
    public:
        PlayerData(int id, int rank, const std::string &username, const std::string &motto,
                   const std::string &figure, PlayerGender gender, bool vip, int credits, int vipPoints,
                   int activityPoints, int seasonalPoints, int createdTimestamp, int lastVisitTimestamp,
                   int favouriteGroup, int currentQuest) : id_(id), rank_(rank), username_(username),
                                                           motto_(motto), figure_(figure), gender_(gender),
                                                           vip_(vip), credits_(credits), vipPoints_(vipPoints),
                                                           activityPoints_(activityPoints),
                                                           seasonalPoints_(seasonalPoints),
                                                           createdTimestamp_(createdTimestamp),
                                                           lastVisitTimestamp_(lastVisitTimestamp),
                                                           favouriteGroup_(favouriteGroup),
                                                           currentQuest_(currentQuest) {}

        ~PlayerData() {}

        int getId() const {
            return id_;
        }

        void setId(int id_) {
            PlayerData::id_ = id_;
        }

        int getRank() const {
            return rank_;
        }

        void setRank(int rank_) {
            PlayerData::rank_ = rank_;
        }

        const std::string &getUsername() const {
            return username_;
        }

        void setUsername(const std::string &username_) {
            PlayerData::username_ = username_;
        }

        const std::string &getMotto() const {
            return motto_;
        }

        void setMotto(const std::string &motto_) {
            PlayerData::motto_ = motto_;
        }

        const std::string &getFigure() const {
            return figure_;
        }

        void setFigure(const std::string &figure_) {
            PlayerData::figure_ = figure_;
        }

        PlayerGender getGender() const {
            return gender_;
        }

        void setGender(PlayerGender gender_) {
            PlayerData::gender_ = gender_;
        }

        bool isVip() const {
            return vip_;
        }

        void setVip(bool vip_) {
            PlayerData::vip_ = vip_;
        }

        int getCredits() const {
            return credits_;
        }

        void setCredits(int credits_) {
            PlayerData::credits_ = credits_;
        }

        int getVipPoints() const {
            return vipPoints_;
        }

        void setVipPoints(int vipPoints_) {
            PlayerData::vipPoints_ = vipPoints_;
        }

        int getActivityPoints() const {
            return activityPoints_;
        }

        void setActivityPoints(int activityPoints_) {
            PlayerData::activityPoints_ = activityPoints_;
        }

        int getSeasonalPoints() const {
            return seasonalPoints_;
        }

        void setSeasonalPoints(int seasonalPoints_) {
            PlayerData::seasonalPoints_ = seasonalPoints_;
        }

        int getCreatedTimestamp() const {
            return createdTimestamp_;
        }

        void setCreatedTimestamp(int createdTimestamp_) {
            PlayerData::createdTimestamp_ = createdTimestamp_;
        }

        int getLastVisitTimestamp() const {
            return lastVisitTimestamp_;
        }

        void setLastVisitTimestamp(int lastVisitTimestamp_) {
            PlayerData::lastVisitTimestamp_ = lastVisitTimestamp_;
        }

        int getFavouriteGroup() const {
            return favouriteGroup_;
        }

        void setFavouriteGroup(int favouriteGroup_) {
            PlayerData::favouriteGroup_ = favouriteGroup_;
        }

        int getCurrentQuest() const {
            return currentQuest_;
        }

        void setCurrentQuest(int currentQuest_) {
            PlayerData::currentQuest_ = currentQuest_;
        }


    private:
        int id_;

        int rank_;
        std::string username_;
        std::string motto_;
        std::string figure_;
        PlayerGender gender_;

        bool vip_;
        int credits_;
        int vipPoints_;

        int activityPoints_;
        int seasonalPoints_;

        int createdTimestamp_;
        int lastVisitTimestamp_;

        int favouriteGroup_;
        int currentQuest_;
    };

    class PlayerDataFactory {
    public:
        std::unique_ptr<PlayerData> create(int id, int rank, const std::string &username, const std::string &motto,
                                           const std::string &figure, PlayerGender gender, bool vip, int credits,
                                           int vipPoints,
                                           int activityPoints, int seasonalPoints, int createdTimestamp,
                                           int lastVisitTimestamp,
                                           int favouriteGroup, int currentQuest) {
            return std::make_unique<PlayerData>(id, rank, username, motto, figure, gender, vip, credits, vipPoints,
                                                activityPoints, seasonalPoints, createdTimestamp, lastVisitTimestamp,
                                                favouriteGroup, currentQuest);
        }
    };
}