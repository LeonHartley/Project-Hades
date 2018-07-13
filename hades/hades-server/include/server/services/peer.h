#pragma once

#include <common/comms/service.h>
#include <string>

namespace hades {
    struct PeerServiceConfig {
        std::string host;
        short port;
    };

    class PeerService : public Service<PeerServiceConfig> {
    public:
        PeerService(ServiceType serviceType, const PeerServiceConfig &config);
    };
}