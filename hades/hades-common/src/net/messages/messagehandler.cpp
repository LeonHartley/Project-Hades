#include <common/net/messages/messagehandler.h>
#include <common/log/log.h>

using namespace hades;

auto const log = LoggerProvider::get("MessageDispatch");

void MessageDispatch::dispatch(hades::Session *session, std::unique_ptr<hades::Buffer> buffer) {
    if (handlers_.size() == 0) {
        handlers_[4000] = HandshakeHandler::readRelease;
        handlers_[286] = HandshakeHandler::authentication;
    }

    const short header = buffer->read<short>();
    const MessageHandler handler = handlers_[header];

    if (handler != nullptr) {
        handlers_[header](session, std::move(buffer));
    } else {
        log->debug("Unhandled message with id %v", header);
    }
}
