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

    private:
        Session *session_;
        std::unique_ptr<PlayerData> playerData_;
    };

    class PlayerContext : public SessionContext {
    public:
        PlayerContext(std::unique_ptr<Player> player, Session *session) : SessionContext(),
                                                                          player_(std::move(player)) {

        }

        virtual void handleMessage(std::unique_ptr<Buffer> buffer);

    private:
        std::unique_ptr<Player> player_;
    };
}