#include <protocol/handlers/handshake.h>
#include <common/log/log.h>
#include <protocol/composers/notifications.h>
#include <storage/storagectx.h>

using namespace hades;

const auto log = LoggerProvider::get("HandshakeHandler");

void HandshakeHandler::readRelease(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto version = buffer->read<std::string>();

    log->info("Client with version %v", version);
}

void HandshakeHandler::authentication(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto sso = buffer->read<std::string>();

    auto player = StorageCtx::players()->getDataByTicket(sso);

    if(player != nullptr) {
        session->send(AuthenticationOKMessageComposer());

        std::string msg = "Hi ";

        session->send(MotdNotificationMessageComposer(msg.append(player->getUsername())));
    }

    log->info("User with SSO %v", sso);
}
