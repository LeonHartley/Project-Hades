#pragma once

#include <common/util/lock.h>
#include <map>

namespace hades {
    class RoomDirectory {
    public:
        static bool isActive(int roomId);

        static int roomServiceByRoomId(int roomId);

        static void addActiveRoom(int roomId, int roomService);

        static void removeActiveRoom(int roomId);

    private:
        static RwMutex mutex_;
        static std::map<int, int> directory_;
    };
}