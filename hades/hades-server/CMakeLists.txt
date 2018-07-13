include_directories(include/  ${HADES_INCLUDES} ${VENDOR_INCLUDES})

add_executable(hades-server
        src/main.cpp src/comms/serversubscriber.cpp include/server/comms/serversubscriber.h src/services/peer.cpp include/server/services/peer.h src/services/room.cpp include/server/services/room.h)

target_link_libraries(hades-server
        hades-common
        hades-storage
        hades-protocol
        uv)