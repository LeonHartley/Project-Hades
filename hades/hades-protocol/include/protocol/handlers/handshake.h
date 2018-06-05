#pragma once

#include <memory>
#include <common/net/session/session.h>
#include <common/player/player.h>


namespace hades {
    class HandshakeHandler {

    public:
        static void readRelease(Session *session, std::unique_ptr<Buffer> buffer);

        static void authentication(Session *session, std::unique_ptr<Buffer> buffer);

        static void infoRetrieve(Player *session, std::unique_ptr<Buffer> buffer);
    };
}
