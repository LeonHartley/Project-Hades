#include <iostream>
#include <common/log/log.h>
#include <protocol/MotdNotificationComposer.h>
#include "common/net/streamhandler.h"

using namespace hades;

const auto log = LoggerProvider::get("StreamHandler");

void StreamHandler::onConnectionOpen(Session *session) {

}

void StreamHandler::onConnectionClosed(Session *session) {

}

void StreamHandler::onReceiveData(Session *session, std::unique_ptr<Buffer> buffer) {
    while(buffer->hasData() && buffer->bytesRemaining() >= 6 /* minimum message length */) {
        const int start = buffer->readerIndex();

        const int length = buffer->read<int>();
        const short header = buffer->read<short>();

        if(header == 4000) {
            const std::string version = buffer->read<std::string>();

            log->info("Client with version %v", version);

            session->send(MotdNotificationComposer());
        }

        log->debug("Message received with length %v, header: %v", length, header);
    }
}