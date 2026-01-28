cmake_minimum_required(VERSION 3.17)
project(ProcessControl-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_definitions(-DSM_BUSNAME=sessionBus)

find_package(Qt6 REQUIRED COMPONENTS DBus Qml)

file(GLOB PROCESS_CONTROL_FILES "*.h" "*.cpp")

qt_add_qml_module(ProcessControl-qml
    URI ProcessControl
    VERSION 0.1
    SOURCES
    ${PROCESS_CONTROL_FILES}
)

target_link_libraries(ProcessControl-qml
    PRIVATE
    Qt6::DBus Qt6::Qml
)

target_include_directories(ProcessControl-qml PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(DBUS_IFACE_DIR "${CMAKE_INSTALL_PREFIX}/share/dbus-1/interfaces")

install(FILES com.lomiri.ProcessControl.xml
    DESTINATION "${DBUS_IFACE_DIR}"
)



