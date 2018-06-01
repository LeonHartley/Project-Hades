
include_directories(include/)
add_library(hades-protocol STATIC
        include/protocol/MotdNotificationComposer.h
        )

target_link_libraries(hades-protocol hades-common hades-storage)