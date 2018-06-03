#pragma once

#include <map>
#include <memory>
#include <vector>

#include <common/net/buffer.h>
#include <common/net/session/session.h>
#include <protocol/handlers/handshake.h>

namespace hades {
    typedef void (*MessageHandler)(Session *, std::unique_ptr<Buffer> buffer);

    class MessageDispatch {
    public:
        void dispatch(Session *session, std::unique_ptr<Buffer> buffer) {
            if (handlers_.size() == 0) {
                handlers_[4000] = HandshakeHandler::readRelease;
            }

            const short header = buffer->read<short>();
            const MessageHandler handler = handlers_[header];

            if (handler != nullptr) {
                handlers_[header](session, std::move(buffer));
            }
        }

    private:
        std::map<short, MessageHandler> handlers_;
    };
}
