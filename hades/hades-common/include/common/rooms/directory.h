#pragma once

#include <common/util/lock.h>
#include <map>

namespace hades {
    class RoomDirectory {
        static bool isActive(int roomId);

        static void activeRoom(int roomId, int roomService);

        static void removeActiveRoom(int roomId);

    private:
        static RwMutex mutex_;
        static std::map<int, int> directory_;
    };
}