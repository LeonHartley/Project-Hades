#include <iostream>
#include <common/log/log.h>
#include <protocol/composers/notifications.h>
#include "common/net/streamhandler.h"

using namespace hades;

const auto log = LoggerProvider::get("StreamHandler");

void StreamHandler::onConnectionOpen(Session *session) {

}

void StreamHandler::onConnectionClosed(Session *session) {

}

void StreamHandler::onReceiveData(Session *session, std::unique_ptr<Buffer> buffer) {
    const int length = buffer->read<int>();

    log->debug("Message received with length %v", length);

    session->context()->handleMessage(session, std::move(buffer));
}