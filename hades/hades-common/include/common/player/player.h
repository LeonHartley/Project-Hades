#pragma once

#include <common/container.h>
#include <common/net/session/session.h>

namespace hades {
    class PlayerComponent {

    };

    class Player : public Container<PlayerComponent> {
    public:
        Player(Session *session, std::unique_ptr<PlayerData> data) : session_(session),
                                                                     playerData_(std::move(data)) {

        }

        void send(const Message &message) {
            session_->send(std::move(message));
        }

        PlayerData *data() {
            return this->playerData_.get();
        }
    private:
        Session *session_;
        std::unique_ptr<PlayerData> playerData_;
    };

    class PlayerContext : public SessionContext {
    public:
        PlayerContext(std::unique_ptr<Player> player, Session *session) : SessionContext(),
                                                                          player_(std::move(player)) {

        }

        void handleMessage(Session *session, std::unique_ptr<Buffer> buffer) override;

    private:
        std::unique_ptr<Player> player_;
    };
}