#pragma once

#include <common/comms/subscriber.h>
#include <common/rooms/directory.h>

namespace hades {
    namespace remote {
        static const short OnPlayerActive = 1001;
        static const short OnPlayerInactive = 1002;
        static const short OnComposeMessage = 1003;

        static const short OnRoomActive = 2001;
        static const short OnRoomInactive = 2002;
    }

    class ServerSubscriber : public RemoteSubscriber {
    public:
        ServerSubscriber() : RemoteSubscriber(
                {{remote::OnPlayerActive,   &onPlayerActive},
                 {remote::OnPlayerInactive, &onPlayerInactive},
                 {remote::OnRoomActive,     &onRoomActive},
                 {remote::OnRoomInactive,   &onRoomInactive}}) {}

    private:
        static void onPlayerActive(std::string id, std::unique_ptr<Buffer> msg);

        static void onPlayerInactive(std::string id, std::unique_ptr<Buffer> msg);

        static void onRoomActive(std::string id, std::unique_ptr<Buffer> msg) {
            const auto roomId = msg->read<int>();
            const auto serviceId = msg->read<int>();

            RoomDirectory::addActiveRoom(roomId, serviceId);
        }

        static void onRoomInactive(std::string id, std::unique_ptr<Buffer> msg) {
            const auto roomId = msg->read<int>();

            RoomDirectory::removeActiveRoom(roomId);
        }
    };
}