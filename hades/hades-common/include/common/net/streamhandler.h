#pragma once

#include <common/net/session/session.h>
#include <common/net/buffer.h>

namespace hades {
    class StreamHandler {
    public:
        void onConnectionOpen(Session *session);

        void onConnectionClosed(Session *session);

        void onReceiveData(Session *session, std::unique_ptr<Buffer> buffer);
    };

}