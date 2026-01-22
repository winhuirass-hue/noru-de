cmake_minimum_required(VERSION 3.24)
project(SessionBroadcast-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

find_package(Qt6 COMPONENTS DBus Qml REQUIRED)

add_definitions(-DSM_BUSNAME=systemBus)

include_directories(${GLIB_INCLUDE_DIRS})

file(GLOB SESSION_BROADCAST_FILES "*.h" "*.cpp")

qt_add_qml_module(SessionBroadcast-qml
    URI SessionBroadcast
    VERSION 0.1
    SOURCES
        ${SESSION_BROADCAST_FILES}
)

target_link_libraries(SessionBroadcast-qml
    PRIVATE
    Qt6::DBus
    Qt6::Qml
    ${GLIB_LIBRARIES}
)
