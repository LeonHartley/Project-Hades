
include_directories(include/)
add_library(hades-storage STATIC
        src/storagectx.cpp include/storage/storagectx.h)
target_link_libraries(hades-storage hades-common)