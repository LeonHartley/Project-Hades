#pragma once

#include <map>
#include <memory>
#include <vector>

#include <common/net/buffer.h>
#include <common/net/session/session.h>
#include <protocol/handlers/handshake.h>

namespace hades {
    typedef void (*MessageHandler)(Session *, std::shared_ptr<Buffer> buffer);

    class MessageDispatch {
    public:
        void dispatch(Session *session, std::shared_ptr<Buffer> buffer) {
            if(handlers_.size() == 0) {
                handlers_[4000] = HandshakeHandler::readRelease;
            }

            const short header = buffer->read<short>();
            handlers_[header](session, buffer);
        }

    private:
        std::map<short, MessageHandler> handlers_;
    };
}
