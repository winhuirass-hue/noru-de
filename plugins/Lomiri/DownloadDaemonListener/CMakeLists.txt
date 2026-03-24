cmake_minimum_required(VERSION 3.17)
project(DownloadDaemonListener VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS Qml Quick DBus Core)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

set(CMAKE_BUILD_RPATH "/usr/local/lib")
set(CMAKE_INSTALL_RPATH "/usr/local/lib")

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDLADAPTER REQUIRED ldm-common-qt6)

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h"   "interface/*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp" "interface/*.cpp")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt_add_qml_module(DownloadDaemonListener
    URI Lomiri.DownloadDaemonListener
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES})

add_definitions(${DDLADAPTER_CFLAGS} ${DDLADAPTER_CFLAGS_OTHER})

target_link_libraries(DownloadDaemonListener
    PRIVATE
    ${QT_LIBS}
    ${DDLADAPTER_LIBRARIES}
)





