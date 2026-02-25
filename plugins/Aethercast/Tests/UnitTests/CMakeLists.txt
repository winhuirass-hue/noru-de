cmake_minimum_required(VERSION 3.17)
project(AethercastTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test DBus Qml)

enable_testing()

qt_add_dbus_interface(
    DBUS_INTERFACE
    ../../org.aethercast.xml
    org_aethercast
)

qt_add_dbus_interface(
    FREEDESKTOP_PROPERTIES
    ../../org.freedesktop.DBus.Properties.xml
    freedesktop_properties
)

add_executable(AethercastTest
    tst_aethercast.cpp
    ../../displays.cpp
    ${DBUS_INTERFACE}
    ${FREEDESKTOP_PROPERTIES}
)

target_include_directories(AethercastTest
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(AethercastTest 
    PRIVATE 
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

add_test(NAME Aethercast COMMAND AethercastTest)
