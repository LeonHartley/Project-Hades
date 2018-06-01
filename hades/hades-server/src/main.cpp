#include <iostream>
#include <memory>

#include <common/net/buffer.h>
#include <common/net/serverbuilder.h>
#include <common/log/log.h>

#include <storage/storagectx.h>

INITIALIZE_EASYLOGGINGPP

using namespace hades;

int main(int argc, char *argv[]) {
    uv_loop_t netLoop;
    uv_loop_init(&netLoop);

    LOG(INFO) << "test test test";
    LOG(INFO) << "yoo";

    StorageCtx::initialise();

    std::unique_ptr<GameServer> gameServer = ServerBuilder::newBuilder()
            ->host("0.0.0.0")
            ->port(1234)
            ->streamHandler(StreamHandler())
            ->uvLoop(&netLoop)
            ->create();

    gameServer->start();
}