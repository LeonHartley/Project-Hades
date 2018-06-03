
include_directories(include/)
add_library(hades-protocol STATIC
        include/protocol/composers/MotdNotificationComposer.h
        include/protocol/handlers/handshake.h src/handlers/handshake.cpp)

target_link_libraries(hades-protocol hades-common hades-storage)