cmake_minimum_required(VERSION 3.24)
project(Platform-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS DBus Qml REQUIRED)

file(GLOB PLATFORM_FILES "*.h" "*.cpp")

qt_add_qml_module(Platform-qml
    URI Lomiri.Platform
    VERSION 1.0
    SOURCES
    ${PLATFORM_FILES}
)

target_link_libraries(Platform-qml
    PRIVATE
    Qt6::DBus
    Qt6::Qml)

