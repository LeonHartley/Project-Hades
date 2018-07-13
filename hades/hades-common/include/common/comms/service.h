#pragma once

namespace hades {
    enum ServiceType {
        PEER,
        ROOM
    };

    template<typename ServiceConfig>
    class Service {
    public:
        Service(ServiceType serviceType, ServiceConfig config) : serviceType_(serviceType),
                                                                 serviceConfig_(config) {

        }

        virtual void start() {

        }

        ServiceType serviceType() {
            return serviceType_;
        }

        ServiceConfig config() {
            return serviceConfig_;
        }

    private:
        ServiceType serviceType_;
        ServiceConfig serviceConfig_;
    };
}