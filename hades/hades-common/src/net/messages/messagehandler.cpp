#include <common/net/messages/messagehandler.h>
#include <common/log/log.h>
#include <common/net/session/session.h>
#include <common/player/player.h>

using namespace hades;

auto const logger = LoggerProvider::get("MessageDispatch");

typedef void (*SessionMessageHandler)(Session *, std::unique_ptr<Buffer> buffer);

typedef void (*PlayerMessageHandler)(Player *, std::unique_ptr<Buffer> buffer);

static const std::map<short, SessionMessageHandler> basicHandlers = {
        {4000, &HandshakeHandler::readRelease},
        {286,  &HandshakeHandler::authentication}
};

static const std::map<short, PlayerMessageHandler> playerHandlers = {
        {2401, &HandshakeHandler::infoRetrieve}
};

void MessageDispatch::dispatch(hades::Session *session, std::unique_ptr<hades::Buffer> buffer) {
    const short header = buffer->read<short>();
    const SessionMessageHandler handler = basicHandlers.find(header)->second;

    if (handler != nullptr) {
        handler(session, std::move(buffer));
    } else {
        logger->debug("Unhandled message with id %v", header);
    }
}

void MessageDispatch::dispatch(hades::Player *player, std::unique_ptr<hades::Buffer> buffer) {
    const short header = buffer->read<short>();
    const PlayerMessageHandler handler = playerHandlers.find(header)->second;

    if (handler != nullptr) {
        handler(player, std::move(buffer));
    } else {
        logger->debug("Unhandled message with id %v", header);
    }
}
