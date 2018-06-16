#pragma once

#include <common/comms/comms.h>
#include <map>

namespace hades {
    typedef void (*RemoteMessageHandler)(std::string id, std::unique_ptr<Buffer> buffer);

    class RemoteSubscriber : public CommunicationSubscriber {

    public:
        RemoteSubscriber(std::map<short, RemoteMessageHandler> handlers) : handlers_(handlers) {

        }

    private:
        std::map<short, RemoteMessageHandler> handlers_;
    };
}