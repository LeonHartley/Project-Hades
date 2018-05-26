#pragma once

#include <uv.h>
#include <common/net/session/sessionfactory.h>

namespace hades {
    class StreamHandler {
    public:
        void onConnectionOpen(uv_stream_t *stream);

        void onConnectionClosed(uv_stream_t *stream);

    protected:
        SessionFactory sessionFactory_;
    };

}