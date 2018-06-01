#include <iostream>
#include "common/net/streamhandler.h"

using namespace hades;

void StreamHandler::onConnectionOpen(Session *session) {
//    Session *session = sessionFactory_.createSession(stream);
//
//    stream->data = static_cast<void *>(session);
}

void StreamHandler::onConnectionClosed(Session *session) {
    //
}

void StreamHandler::onReceiveData(Session *session, std::unique_ptr<Buffer> buffer) {
    std::cout << "yoyo " << session << " " << buffer.get() << "\n";
}