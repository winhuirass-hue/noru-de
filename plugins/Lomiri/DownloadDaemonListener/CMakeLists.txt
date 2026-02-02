cmake_minimum_required(VERSION 3.24)
project(DownloadDaemonListener LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Qml Quick DBus Core)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDLADAPTER REQUIRED ldm-common-qt6)

file(GLOB DOWNLOAD_DAEMON_LISTENER_FILES "*.cpp" "*.h" "interface/*.cpp" "interface/*.h")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

qt_add_qml_module(DownloadDaemonListener
    URI Lomiri.DownloadDaemonListener
    VERSION 0.1
    SOURCES
    ${DOWNLOAD_DAEMON_LISTENER_FILES})


add_definitions(${DDLADAPTER_CFLAGS} ${DDLADAPTER_CFLAGS_OTHER})

target_link_libraries(DownloadDaemonListener
    PRIVATE
    Qt6::Qml Qt6::Quick Qt6::DBus Qt6::Core
    ${DDLADAPTER_LIBRARIES}
)






