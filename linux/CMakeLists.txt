cmake_minimum_required(VERSION 3.28)
project(douki)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_PREFIX_PATH /usr/include/)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk4)

pkg_search_module(UUID REQUIRED uuid)
pkg_search_module(JSONGLIB REQUIRED json-glib-1.0)
pkg_search_module(AVAHI REQUIRED avahi-client)

set(
    SOURCE

    src/core/auth/auth-manager.c
    src/core/dbus/authentication.c
    src/core/mdns/mdns.c
    src/core/socket/device-connection.c
    src/core/socket/socket.c
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