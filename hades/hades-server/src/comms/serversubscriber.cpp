//
// Created by Leon on 16/06/2018.
//

#include "server/comms/serversubscriber.h"

using namespace hades;

void ServerSubscriber::onPlayerActive(std::string id, std::unique_ptr<hades::Buffer> msg) {
    //
}

void ServerSubscriber::onPlayerInactive(std::string id, std::unique_ptr<Buffer> msg) {
    // Update directory, notify online players
}
