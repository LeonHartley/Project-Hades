#include <iostream>
#include <common/net/buffer.h>
#include <common/container.h>
#include <memory>

using namespace hades;

class PlayerComponent {
public:
    PlayerComponent() {

    }
};

class Player : public Container<PlayerComponent> {

};

class PermissionComponent : public PlayerComponent {
public:
    PermissionComponent() = default;

    void test() {
        std::cout << "Hey! :o\n";
    }
};

int main() {

    auto player = std::make_shared<Player>();

    // register components
    player->component(std::make_shared<PermissionComponent>());

    auto permissions = player->component<PermissionComponent>();

    permissions->test();
}
