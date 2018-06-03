#pragma once

#include <memory>
#include <common/net/session/session.h>
#include <common/net/buffer.h>
#include <common/net/messages/messagehandler.h>

namespace hades {
    class StreamHandler {
    public:
        StreamHandler() : messageDispatch_(MessageDispatch()) {

        }

    public:
        void onConnectionOpen(Session *session);

        void onConnectionClosed(Session *session);

        void onReceiveData(Session *session, std::unique_ptr<Buffer> buffer);

    private:
        MessageDispatch messageDispatch_;
    };

}