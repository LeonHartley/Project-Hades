#pragma once

#include <uv.h>
#include <memory>
#include "session.h"

namespace hades {
    class SessionFactory {
    public:
        virtual Session *createSession(uv_stream_t *client) {
            return new Session(client);
        }

        virtual void disposeSession(Session *session) {
            // dispose session components
            delete session;
        }
    };
}