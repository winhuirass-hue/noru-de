cmake_minimum_required(VERSION 3.24)
project(LomiriSession-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS DBus Qml REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GIO_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${liblomiri-private_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/../../../src/liblomiri-private
)

add_definitions(-DQT_NO_KEYWORDS)
add_definitions(-DSM_BUSNAME=systemBus)

file(GLOB LOMIRI_SESSION_FILES "*.h" "*.cpp")

qt_add_qml_module(LomiriSession-qml
    URI Lomiri.Session
    VERSION 0.1
    SOURCES
    ${LOMIRI_SESSION_FILES}
)

target_link_libraries(LomiriSession-qml
    PRIVATE
    Qt6::DBus Qt6::Qml
    lomiri-private
    ${GIO_LDFLAGS}
    ${GLIB_LIBRARIES}
    )
