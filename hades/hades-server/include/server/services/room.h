#pragma once

#include <common/comms/service.h>

namespace hades {
    class RoomServiceConfig {

    };

    class RoomService : Service<RoomServiceConfig> {
    public:
        RoomService(ServiceType serviceType, const RoomServiceConfig &config);

    };

}