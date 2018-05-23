include_directories(include/)

add_executable(hades-server
    src/main.cpp ../hades-common/include/common/config.h)

target_link_libraries(hades-server hades-common uv)