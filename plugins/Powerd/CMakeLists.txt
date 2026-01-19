cmake_minimum_required(VERSION 3.17)
project(Powerd LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED glib-2.0 gio-2.0)
find_package(Qt6DBus REQUIRED)
find_package(Qt6Qml REQUIRED)

add_definitions(-DQT_NO_KEYWORDS)

include_directories(
    ${GIO_INCLUDE_DIRS}
)

qt_add_qml_module(Powerd-qml
    URI Powerd
    VERSION 0.1
    SOURCES
    Powerd.h
    Powerd.cpp
)

add_definitions(-DSM_BUSNAME=systemBus)

target_link_libraries(Powerd-qml
    PRIVATE
    Qt6::DBus Qt6::Qml
    ${GIO_LDFLAGS}
)

