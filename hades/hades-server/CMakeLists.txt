include_directories(include/)

add_executable(hades-server
    src/main.cpp)

target_link_libraries(hades-server
        hades-common
        hades-storage
        uv)