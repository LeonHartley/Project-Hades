#include <iostream>
#include <common/log/log.h>
#include <protocol/composers/MotdNotificationComposer.h>
#include "common/net/streamhandler.h"

using namespace hades;

const auto log = LoggerProvider::get("StreamHandler");

void StreamHandler::onConnectionOpen(Session *session) {

}

void StreamHandler::onConnectionClosed(Session *session) {

}

void StreamHandler::onReceiveData(Session *session, std::shared_ptr<Buffer> buffer) {
    while (buffer->hasData() && buffer->bytesRemaining() >= 6 /* minimum message length */) {
        const int start = buffer->readerIndex();

        const int length = buffer->read<int>();

        log->debug("Message received with length %v", length);
        this->messageDispatch_.dispatch(session, buffer);
    }
}