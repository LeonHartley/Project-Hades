
include_directories(include/)
add_library(hades-common STATIC
        include/game/net/server.h
        include/game/net/serverbuilder.h
        src/test.cpp)