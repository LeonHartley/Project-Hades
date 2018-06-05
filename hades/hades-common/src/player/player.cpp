#include <common/player/player.h>
#include <common/net/messages/messagehandler.h>

void hades::PlayerContext::handleMessage(std::unique_ptr<hades::Buffer> buffer) {
    MessageDispatch::dispatch(this->player_.get(), std::move(buffer));
}
