#pragma once

#include <uv.h>
#include <memory>
#include <common/net/session/session.h>

namespace hades {
    class SessionFactory {
    public:
        SessionFactory() = default;

        virtual Session *createSession(uv_stream_t *client) {
            return new Session(client);
        }

        virtual void disposeSession(Session *session) {
            // dispose session components
            delete session;
        }
    };
}