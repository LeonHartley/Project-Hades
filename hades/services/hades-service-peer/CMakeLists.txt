include_directories(include/  ${HADES_INCLUDES} ${VENDOR_INCLUDES})

add_executable(hades-service-peer
        )

target_link_libraries(hades-server
        hades-common
        hades-storage
        hades-protocol
        uv)