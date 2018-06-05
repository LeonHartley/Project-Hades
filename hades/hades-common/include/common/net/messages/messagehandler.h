#pragma once

#include <map>
#include <memory>
#include <vector>

#include <common/net/buffer.h>
#include <protocol/handlers/handshake.h>
#include <mutex>
#include <common/player/player.h>
#include <common/net/session/session.h>

namespace hades {

    class MessageDispatch {
    public:
        static void dispatch(Session *session, std::unique_ptr<Buffer> buffer);

        static void dispatch(Player *player, std::unique_ptr<Buffer> buffer);
    };
}
