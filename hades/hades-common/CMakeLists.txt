
include_directories(include/ ${HADES_INCLUDES} ${VENDOR_INCLUDES})

add_library(hades-common STATIC
        ${hiredis}
        include/common/net/server.h
        include/common/net/serverbuilder.h
        include/common/net/session/session.h
        include/common/net/buffer.h
        include/common/file.h
        include/common/container.h
        include/common/net/streamhandler.h
        include/common/net/session/sessionfactory.h
        src/net/buffer.cpp
        src/net/streamhandler.cpp
        src/net/server.cpp
        include/common/ctx/ctx.h
        include/common/net/messages/message.h
        include/common/log/log.h
        src/log/log.cpp
        src/pool.cpp
        include/common/pool.h
        include/common/net/messages/messagehandler.h
        src/net/session/session.cpp
        src/net/messages/messagehandler.cpp
        include/common/comms/comms.h
        src/comms/comms.cpp
        include/common/util/base64.h
        src/util/base64.cpp
        include/common/player/player.h
        src/player/player.cpp
        src/rooms/directory.cpp
        include/common/rooms/directory.h
        include/common/util/lock.h
        include/common/comms/subscriber.h
        include/common/player/directory.h
        include/common/directory.h
        src/comms/service.cpp
        include/common/comms/service.h include/common/util/time.h)

target_link_libraries(hades-common hades-protocol)