cmake_minimum_required(VERSION 3.24)
project(ModemConnectivity LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Qml DBus Core REQUIRED)

file(GLOB MODEM_CONNECTIVITY_FILES "*.h" "*.cpp")

qt_add_qml_module(ModemConnectivity
    URI Lomiri.ModemConnectivity
    VERSION 0.1
    SOURCES
        ${MODEM_CONNECTIVITY_FILES}
)

target_link_libraries(ModemConnectivity
    PRIVATE
    Qt6::Qml
    Qt6::DBus
    Qt6::Core
)
