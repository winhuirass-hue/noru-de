cmake_minimum_required(VERSION 3.17)
project(ProcessControl-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_definitions(-DSM_BUSNAME=sessionBus)

set(QT_COMPONENTS DBus Qml)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp")

qt_add_qml_module(ProcessControl-qml
    URI ProcessControl
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_link_libraries(ProcessControl-qml
    PRIVATE
    ${QT_LIBS}
)

target_include_directories(ProcessControl-qml PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

set(DBUS_IFACE_DIR "${CMAKE_INSTALL_PREFIX}/share/dbus-1/interfaces")

install(FILES com.lomiri.ProcessControl.xml
    DESTINATION "${DBUS_IFACE_DIR}"
)
