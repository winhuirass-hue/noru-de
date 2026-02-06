cmake_minimum_required(VERSION 3.24)
project(ApplicationMenu-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS DBus Qml Quick REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB APPLICATION_MENU_FILES "*.h" "*.cpp")

qt_add_dbus_adaptor(DBUS_ADAPTOR_SRCS
    com.lomiri.MenuRegistrar.xml
    dbusapplicationmenuregistry.h
    DBusApplicationMenuRegistry
)
qt_add_qml_module(ApplicationMenu-qml
    URI Lomiri.ApplicationMenu
    VERSION 0.1
    SOURCES
    ${APPLICATION_MENU_FILES}
    ${DBUS_ADAPTOR_SRCS}
)

target_link_libraries(ApplicationMenu-qml
    PRIVATE Qt6::DBus Qt6::Qml Qt6::Quick)

