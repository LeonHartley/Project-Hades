#pragma once

#include <common/net/session/session.h>
#include <memory>

namespace hades {
    class HandshakeHandler {

    public:
        static void readRelease(Session *session, std::unique_ptr<Buffer> buffer);
    };
}
