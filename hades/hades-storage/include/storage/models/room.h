#pragma once

#include <string>
#include <map>

namespace hades {
    enum TradeState {
        OWNER_ONLY, ENABLED, DISABLED
    };

    enum MuteState {
        NONE, RIGHTS
    };

    enum KickState {
        NONE, RIGHTS, EVERYONE
    };

    enum BanState {
        NONE, RIGHTS
    };

    enum RoomType {
        PUBLIC, PRIVATE
    };

    enum AccessType {
        PASSWORD, DOORBELL, OPEN, INVISIBLE
    };

    class RoomData {

    public:
        RoomData(const int id, const RoomType type, const int ownerId, const std::string &ownerName, int groupId,
                 const std::string &name, const std::string &description, const std::string &password,
                 AccessType accessType, int categoryId, int maxPlayers, int score, bool allowPets,
                 bool allowPetsEat, bool allowEntityCollisions, bool wallsHidden, int thicknessWall,
                 int thicknessFloor, const std::map<std::string, std::string> &decorations, int bubbleMode,
                 int bubbleType, int bubbleScroll, int bubbleDistance, int floodLevel, TradeState tradeState,
                 MuteState muteState, KickState kickState, BanState banState) : id_(id), type_(type),
                                                                                ownerId_(ownerId),
                                                                                ownerName_(ownerName),
                                                                                groupId_(groupId), name_(name),
                                                                                description_(description),
                                                                                password_(password),
                                                                                accessType_(accessType),
                                                                                categoryId_(categoryId),
                                                                                maxPlayers_(maxPlayers),
                                                                                score_(score),
                                                                                allowPets_(allowPets),
                                                                                allowPetsEat_(allowPetsEat),
                                                                                allowEntityCollisions_(
                                                                                        allowEntityCollisions),
                                                                                wallsHidden_(wallsHidden),
                                                                                thicknessWall_(thicknessWall),
                                                                                thicknessFloor_(thicknessFloor),
                                                                                decorations_(decorations),
                                                                                bubbleMode_(bubbleMode),
                                                                                bubbleType_(bubbleType),
                                                                                bubbleScroll_(bubbleScroll),
                                                                                bubbleDistance_(bubbleDistance),
                                                                                floodLevel_(floodLevel),
                                                                                tradeState_(tradeState),
                                                                                muteState_(muteState),
                                                                                kickState_(kickState),
                                                                                banState_(banState) {}

        const int getId() const {
            return id_;
        }

        const RoomType getType() const {
            return type_;
        }

        const int getOwnerId() const {
            return ownerId_;
        }

        const std::string &getOwnerName() const {
            return ownerName_;
        }

        int getGroupId() const {
            return groupId_;
        }

        void setGroupId(int groupId) {
            groupId_ = groupId;
        }

        const std::string &getName() const {
            return name_;
        }

        void setName(const std::string &name) {
            name_ = name;
        }

        const std::string &getDescription() const {
            return description_;
        }

        void setDescription(const std::string &description) {
            description_ = description;
        }

        const std::string &getPassword() const {
            return password_;
        }

        void setPassword(const std::string &password) {
            password_ = password;
        }

        AccessType getAccessType() const {
            return accessType_;
        }

        void setAccessType(AccessType accessType) {
            accessType_ = accessType;
        }

        int getCategoryId() const {
            return categoryId_;
        }

        void setCategoryId(int categoryId) {
            categoryId_ = categoryId;
        }

        int getMaxPlayers() const {
            return maxPlayers_;
        }

        void setMaxPlayers(int maxPlayers) {
            maxPlayers_ = maxPlayers;
        }

        int getScore() const {
            return score_;
        }

        void setScore(int score) {
            score_ = score;
        }

        bool isAllowPets() const {
            return allowPets_;
        }

        void setAllowPets(bool allowPets) {
            allowPets_ = allowPets;
        }

        bool isAllowPetsEat() const {
            return allowPetsEat_;
        }

        void setAllowPetsEat(bool allowPetsEat) {
            allowPetsEat_ = allowPetsEat;
        }

        bool isAllowEntityCollisions() const {
            return allowEntityCollisions_;
        }

        void setAllowEntityCollisions(bool allowEntityCollisions) {
            allowEntityCollisions_ = allowEntityCollisions;
        }

        bool isWallsHidden() const {
            return wallsHidden_;
        }

        void setWallsHidden(bool wallsHidden) {
            wallsHidden_ = wallsHidden;
        }

        int getThicknessWall() const {
            return thicknessWall_;
        }

        void setThicknessWall(int thicknessWall) {
            thicknessWall_ = thicknessWall;
        }

        int getThicknessFloor() const {
            return thicknessFloor_;
        }

        void setThicknessFloor(int thicknessFloor) {
            thicknessFloor_ = thicknessFloor;
        }

        const std::map<std::string, std::string> &getDecorations() const {
            return decorations_;
        }

        void setDecorations(const std::map<std::string, std::string> &decorations) {
            decorations_ = decorations_;
        }

        int getBubbleMode() const {
            return bubbleMode_;
        }

        void setBubbleMode(int bubbleMode) {
            bubbleMode_ = bubbleMode;
        }

        int getBubbleType() const {
            return bubbleType_;
        }

        void setBubbleType(int bubbleType) {
            bubbleType_ = bubbleType;
        }

        int getBubbleScroll() const {
            return bubbleScroll_;
        }

        void setBubbleScroll(int bubbleScroll) {
            bubbleScroll_ = bubbleScroll;
        }

        int getBubbleDistance() const {
            return bubbleDistance_;
        }

        void setBubbleDistance(int bubbleDistance) {
            bubbleDistance_ = bubbleDistance;
        }

        int getFloodLevel() const {
            return floodLevel_;
        }

        void setFloodLevel(int floodLevel) {
            floodLevel_ = floodLevel;
        }

        TradeState getTradeState() const {
            return tradeState_;
        }

        void setTradeState(TradeState tradeState) {
            tradeState_ = tradeState;
        }

        MuteState getMuteState() const {
            return muteState_;
        }

        void setMuteState(MuteState muteState) {
            muteState_ = muteState;
        }

        KickState getKickState() const {
            return kickState_;
        }

        void setKickState(KickState kickState) {
            kickState_ = kickState;
        }

        BanState getBanState() const {
            return banState_;
        }

        void setBanState(BanState banState) {
            banState_ = banState;
        }

    private:
        const int id_;
        const RoomType type_;
        const int ownerId_;
        const std::string ownerName_;

        int groupId_;

        std::string name_;
        std::string description_;
        std::string password_;

        AccessType accessType_;
        int categoryId_;
        int maxPlayers_;
        int score_;

        bool allowPets_;
        bool allowPetsEat_;
        bool allowEntityCollisions_;
        bool wallsHidden_;
        int thicknessWall_;
        int thicknessFloor_;
        std::map<std::string, std::string> decorations_;

        int bubbleMode_;
        int bubbleType_;
        int bubbleScroll_;
        int bubbleDistance_;
        int floodLevel_;

        TradeState tradeState_;
        MuteState muteState_;
        KickState kickState_;
        BanState banState_;
    };
}