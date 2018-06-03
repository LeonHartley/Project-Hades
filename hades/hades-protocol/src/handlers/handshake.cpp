#include <protocol/handlers/handshake.h>
#include <common/log/log.h>
#include <protocol/composers/notifications.h>

using namespace hades;

const auto log = LoggerProvider::get("HandshakeHandler");

void HandshakeHandler::readRelease(Session *session, std::unique_ptr<Buffer> buffer)  {
    const auto version = buffer->read<std::string>();

    log->info("Client with version %v", version);
    session->send(MotdNotificationMessageComposer("heya ;D"));
}
