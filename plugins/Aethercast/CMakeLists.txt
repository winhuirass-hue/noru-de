cmake_minimum_required(VERSION 3.24)
project(Aethercast-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Qml DBus REQUIRED)

file(GLOB AETHERCAST_FILES "*.h" "*.cpp")

qt_add_dbus_interface(
    DBUS_INTERFACE
    org.aethercast.xml
    org_aethercast
)

qt_add_dbus_interface(
    FREEDESKTOP_PROPERTIES
    org.freedesktop.DBus.Properties.xml
    freedesktop_properties
)

qt_add_qml_module(Aethercast-qml
    URI Aethercast
    VERSION 0.1
    SOURCES
    ${AETHERCAST_FILES}
    ${DBUS_INTERFACE}
    ${FREEDESKTOP_PROPERTIES}
)

target_include_directories(
    Aethercast-qml
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Aethercast-qml PRIVATE Qt6::Qml Qt6::DBus)

