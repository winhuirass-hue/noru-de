cmake_minimum_required(VERSION 3.17)
project(ApplicationMenu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS DBus Qml Quick)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt_add_dbus_adaptor(DBUS_ADAPTOR_SRCS
    com.lomiri.MenuRegistrar.xml
    dbusapplicationmenuregistry.h
    DBusApplicationMenuRegistry
)
qt_add_qml_module(ApplicationMenu-qml
    URI Lomiri.ApplicationMenu
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${DBUS_ADAPTOR_SRCS}
)

target_link_libraries(ApplicationMenu-qml PRIVATE ${QT_LIBS})
