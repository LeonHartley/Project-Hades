
include_directories(include/)
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
        src/net/server.cpp include/common/ctx/ctx.h)