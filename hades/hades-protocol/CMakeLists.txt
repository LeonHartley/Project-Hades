
include_directories(include/)
add_library(hades-protocol STATIC
        include/protocol/composers/notifications.h
        include/protocol/handlers/handshake.h src/handlers/handshake.cpp include/protocol/composers/user.h include/protocol/composers/catalog.h include/protocol/composers/rooms.h include/protocol/composers/balance.h)

target_link_libraries(hades-protocol hades-common hades-storage)