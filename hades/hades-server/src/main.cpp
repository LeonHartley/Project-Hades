#include <iostream>
#include <memory>

#include <common/net/buffer.h>
#include <common/net/serverbuilder.h>

using namespace hades;

int main() {
    auto server = ServerBuilder::newBuilder()
            ->host("0.0.0.0")
            ->port(1234)
            ->streamHandler(StreamHandler())
            ->create();

    server->start();
}
