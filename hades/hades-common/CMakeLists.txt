
include_directories(include/)
add_library(hades-common STATIC
        include/common/net/server.h
        include/common/net/serverbuilder.h
        include/common/test.h
        src/test.cpp
        include/common/net/session.h
        include/common/net/buffer.h
        src/net/buffer.cpp
        include/common/config.h
        include/common/container.h)