
include_directories(include/)
add_library(hades-storage STATIC
        src/storagectx.cpp include/storage/storagectx.h include/storage/repositories/players.h include/storage/models/player.h include/storage/mysql/mysqlplayers.h src/mysql/mysqlplayers.cpp include/storage/mysql/connectionpool.h src/mysql/connectionpool.cpp)

target_link_libraries(hades-storage hades-common mysqlcppconn)