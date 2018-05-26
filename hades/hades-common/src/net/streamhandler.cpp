#include "common/net/streamhandler.h"

using namespace hades;

void StreamHandler::onConnectionOpen(uv_stream_t *stream) {
    Session *session = sessionFactory_.createSession(stream);

    stream->data = static_cast<void *>(session);
}

void StreamHandler::onConnectionClosed(uv_stream_t *stream) {
    auto session = static_cast<Session *>(stream->data);

    sessionFactory_.disposeSession(session);
    stream->data = nullptr;
}