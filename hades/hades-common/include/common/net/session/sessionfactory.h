#pragma once

#include <uv.h>
#include <memory>
#include <common/net/session/session.h>

namespace hades {
    class SessionFactory {
    public:
        SessionFactory() = default;

        virtual std::unique_ptr<Session> createSession(uv_stream_t *client) {
            return std::move(std::make_unique<Session>(client, std::make_unique<SessionContext>()));
        }
    };
}