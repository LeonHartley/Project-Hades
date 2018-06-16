include_directories(include/  ${HADES_INCLUDES} ${VENDOR_INCLUDES})

add_executable(hades-server
    src/main.cpp src/comms/serversubscriber.cpp include/comms/serversubscriber.h)

target_link_libraries(hades-server
        hades-common
        hades-storage
        hades-protocol
        uv)