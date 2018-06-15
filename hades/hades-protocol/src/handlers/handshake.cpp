#include <protocol/handlers/handshake.h>
#include <common/log/log.h>
#include <protocol/composers/notifications.h>
#include <storage/storagectx.h>

#include <common/net/session/session.h>
#include <common/player/player.h>
#include <protocol/composers/user.h>
#include <protocol/composers/catalog.h>
#include <protocol/composers/balance.h>

using namespace hades;

const auto logger = LoggerProvider::get("HandshakeHandler");

void HandshakeHandler::readRelease(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto version = buffer->read<std::string>();

    logger->info("Client with version %v", version);
}

void HandshakeHandler::authentication(Session *session, std::unique_ptr<Buffer> buffer) {
    const auto sso = buffer->read<std::string>();
    auto player = StorageCtx::players()->getDataByTicket(sso);

    if (player == nullptr) {
        session->close();
        return;
    }

    const std::string str = "this is hades";

    session->send(AuthenticationOKMessageComposer());
    session->send(MotdNotificationMessageComposer(std::move(str)));

    session->context(std::make_unique<PlayerContext>(
            std::make_unique<Player>(session, std::move(player)), session));
}

void HandshakeHandler::infoRetrieve(Player *player, std::unique_ptr<Buffer> buffer) {
    player->send(UserObjectMessageComposer(player->data()));
    player->send(FuserightsMessageComposer(true /*give everyone club cos im a nice guy*/, player->data()->getRank()));
    player->send(FavouriteRoomsMessageComposer());
    player->send(BuildersClubMembershipMessageComposer());
    player->send(AllowancesMessageComposer());
    player->send(HomeRoomMessageComposer());

    player->send(CreditBalanceMessageComposer(player->data()->getCredits()));
    player->send(CurrenciesBalanceMessageComposer({
                                                          std::make_tuple(0, player->data()->getActivityPoints()),
                                                          std::make_tuple(105, player->data()->getVipPoints()),
                                                          std::make_tuple(5, player->data()->getVipPoints()),
                                                          std::make_tuple(106, player->data()->getSeasonalPoints())
                                                  }));
}
