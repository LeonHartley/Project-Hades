cmake_minimum_required(VERSION 3.10)

project(hades)

set(HADES_INCLUDES
        "hades/hades-common/include"
        "hades/hades-server/include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

add_subdirectory("hades/hades-server")
add_subdirectory("hades/hades-common")

target_include_directories(hades-server PUBLIC ${HADES_INCLUDES})
