
include_directories(include/ ${HADES_INCLUDES} ${VENDOR_INCLUDES})

add_library(hades-common STATIC
        include/common/net/server.h
        include/common/net/serverbuilder.h
        include/common/net/session/session.h
        include/common/net/buffer.h
        include/common/config.h
        include/common/container.h
        include/common/net/streamhandler.h
        include/common/net/session/sessionfactory.h
        include/common/dispatch/dispatch.h
        src/net/buffer.cpp
        src/net/streamhandler.cpp
        src/net/server.cpp
        include/common/ctx/ctx.h
        include/common/net/messages/message.h
        include/common/log/log.h
        src/log/log.cpp src/pool.cpp include/common/pool.h include/common/net/messages/messagehandler.h src/net/session/session.cpp src/net/messages/messagehandler.cpp ${hiredis} include/common/comms.h src/comms.cpp include/common/util/base64.h src/util/base64.cpp include/common/player/player.h src/player/player.cpp src/dispatch/dispatch.cpp src/rooms/directory.cpp include/common/rooms/directory.h include/common/util/lock.h)

target_link_libraries(hades-common hades-protocol)