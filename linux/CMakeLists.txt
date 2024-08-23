cmake_minimum_required(VERSION 3.28)
project(douki)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_PREFIX_PATH /usr/include/)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)
pkg_check_modules(UUID REQUIRED uuid)
pkg_check_modules(JSONGLIB REQUIRED json-glib-1.0)
pkg_check_modules(AVAHI REQUIRED avahi-client)
pkg_check_modules(SQLITE3 REQUIRED sqlite3)

set(
    SOURCE

    src/core/auth/auth-manager.c
    src/core/dbus/authentication.c
    src/core/device-connection.c
    src/core/device-listener.c
    src/core/process.c

    src/database/entity/entity-device.c
    src/database/entity/entity-info.c
    src/database/database.c

    src/model/device-info.c
    src/model/device-message.c

    src/utils/json-util.c
    src/utils/logger-util.c
    src/utils/socket-util.c
    src/utils/string-util.c

    src/main.c
)
add_executable(douki ${SOURCE})
target_include_directories(douki PRIVATE include/)

target_include_directories(douki PUBLIC ${GTK_INCLUDE_DIRS})
target_link_libraries(douki ${GTK_LIBRARIES})

target_include_directories(douki PUBLIC ${UUID_INCLUDE_DIRS})
target_link_libraries(douki ${UUID_LIBRARIES})

target_include_directories(douki PUBLIC ${JSONGLIB_INCLUDE_DIRS})
target_link_libraries(douki ${JSONGLIB_LIBRARIES})

target_include_directories(douki PUBLIC ${AVAHI_INCLUDE_DIRS})
target_link_libraries(douki ${AVAHI_LIBRARIES})

target_include_directories(douki PUBLIC ${SQLITE3_INCLUDE_DIRS})
target_link_libraries(douki ${SQLITE3_LIBRARIES})