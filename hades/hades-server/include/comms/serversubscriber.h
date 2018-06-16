#pragma once

#include <common/comms/subscriber.h>

namespace hades {
    namespace remote {
        static const short OnPlayerActive = 1001;
        static const short OnPlayerInactive = 1002;

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
        static void onPlayerActive(std::string id, std::unique_ptr<Buffer> msg) {

        }

        static void onPlayerInactive(std::string id, std::unique_ptr<Buffer> msg) {

        }

        static void onRoomActive(std::string id, std::unique_ptr<Buffer> msg) {
            const int roomId = msg->read<int>();

        }

        static void onRoomInactive(std::string id, std::unique_ptr<Buffer> msg) {

        }
    };
}