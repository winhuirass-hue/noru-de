cmake_minimum_required(VERSION 3.16)
project(SessionBroadcast-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS DBus Qml)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "*.cpp")

add_definitions(-DSM_BUSNAME=systemBus)

include_directories(${GLIB_INCLUDE_DIRS})

qt_add_qml_module(SessionBroadcast-qml
    URI SessionBroadcast
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_link_libraries(SessionBroadcast-qml
    PRIVATE
    ${QT_LIBS}
    ${GLIB_LIBRARIES}
)
