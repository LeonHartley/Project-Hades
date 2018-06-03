#pragma once

#include <common/net/session/session.h>
#include <memory>

namespace hades {
    class HandshakeHandler {

    public:
        static void readRelease(Session *session, std::shared_ptr<Buffer> buffer);
    };
}
