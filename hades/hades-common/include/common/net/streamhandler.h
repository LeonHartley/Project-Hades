#pragma once

#include <uv.h>
#include <common/net/session/sessionfactory.h>

namespace hades {
    class StreamHandler {
    public:
        void onConnectionOpen(Session *session);

        void onConnectionClosed(Session *session);

        void onReceiveData(Session *session, std::unique_ptr<Buffer> buffer);
    };

}