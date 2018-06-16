#include "common/rooms/directory.h"

#include <map>
#include <common/util/lock.h>

using namespace hades;

bool RoomDirectory::isActive(int roomId) {
    RwLockGuard lock(&mutex_, READ);
    return directory_.count(roomId) == 1;
}

void RoomDirectory::addActiveRoom(int roomId, int roomService) {
    RwLockGuard lock(&mutex_, WRITE);
    directory_.emplace(roomId, roomService);
}

void RoomDirectory::removeActiveRoom(int roomId) {
    RwLockGuard lock(&mutex_, WRITE);
    directory_.erase(roomId);
}

int RoomDirectory::roomServiceByRoomId(int roomId) {
    RwLockGuard lock(&mutex_, READ);

    if (!directory_.count(roomId)) {
        return -1;
    }

    return directory_.find(roomId)->second;
}
