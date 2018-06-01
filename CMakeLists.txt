cmake_minimum_required(VERSION 3.10)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE STRING "Modules for CMake" FORCE)

project(hades)

set(VENDOR_INCLUDES

        )
set(HADES_INCLUDES
        hades/hades-common/include
        hades/hades-server/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ./bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

find_package (Libuv)

add_subdirectory(hades/hades-server)
add_subdirectory(hades/hades-common)

target_include_directories(hades-common PUBLIC ${VENDOR_INCLUDES})
target_include_directories(hades-server PUBLIC ${HADES_INCLUDES} ${VENDOR_INCLUDES})
