cmake_minimum_required(VERSION 3.17)
project(Aethercast VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS Qml DBus)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")

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
    ${HEADER_FILES}
    ${SOURCE_FILES}
    ${DBUS_INTERFACE}
    ${FREEDESKTOP_PROPERTIES}
)

target_include_directories(
    Aethercast-qml
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(Aethercast-qml PRIVATE ${QT_LIBS})

