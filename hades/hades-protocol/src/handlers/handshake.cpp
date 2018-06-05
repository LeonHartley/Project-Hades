#include <protocol/handlers/handshake.h>
#include <common/log/log.h>
#include <protocol/composers/notifications.h>
#include <storage/storagectx.h>

#include <common/net/session/session.h>
#include <common/player/player.h>
#include <protocol/composers/user.h>

using namespace hades;

const auto log = LoggerProvider::get("HandshakeHandler");

void HandshakeHandler::readRelease(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto version = buffer->read<std::string>();

    log->info("Client with version %v", version);
}

void HandshakeHandler::authentication(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto sso = buffer->read<std::string>();
    auto player = StorageCtx::players()->getDataByTicket(sso);

    if (player == nullptr) {
        session->close();
        return;
    }

    session->send(AuthenticationOKMessageComposer());
    session->send(MotdNotificationMessageComposer("this is hades"));
    session->send(FuserightsMessageComposer(true /*give everyone club cos im a nice guy*/, player->getRank()));

    session->context(std::make_unique<PlayerContext>(
            std::make_unique<Player>(session, std::move(player)), session));
}

void HandshakeHandler::infoRetrieve(Player *player, std::unique_ptr<Buffer> buffer) {
    std::cout << "requestin info for player: " << player->data()->getUsername() << std::endl;
}
