#pragma once

#include <memory>
#include <common/net/session/session.h>
#include <common/net/buffer.h>
#include <common/net/messages/messagehandler.h>

namespace hades {
    class StreamHandler {

    public:
        void onConnectionOpen(Session *session);

        void onConnectionClosed(Session *session);

        void onReceiveData(Session *session, std::unique_ptr<Buffer> buffer);
    };

}