#pragma once

#include <common/comms/comms.h>
#include <map>
#include <memory>

namespace hades {
    typedef void (*RemoteMessageHandler)(std::string id, std::unique_ptr<Buffer> buffer);

    class RemoteSubscriber : public CommunicationSubscriber {

    public:
        RemoteSubscriber(std::map<short, RemoteMessageHandler> handlers) : handlers_(handlers) {

        }

        void onMessage(Communication *ctx, short type, std::string id, std::unique_ptr<Buffer> msg) override {
            if(handlers_.count(type)) {
                handlers_[type](std::move(id), std::move(msg));
            }
        }

    private:
        std::map<short, RemoteMessageHandler> handlers_;
    };
}