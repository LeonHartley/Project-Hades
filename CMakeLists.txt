cmake_minimum_required(VERSION 3.10)

project(hades)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("hades/hades-common")
add_subdirectory("hades/hades-server")

target_include_directories(hades-server PUBLIC "hades/hades-common/include")
