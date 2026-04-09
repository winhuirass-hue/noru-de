cmake_minimum_required(VERSION 3.17)
project(LomiriLauncherAS-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSETTINGS_QT REQUIRED gsettings-qt)

find_package(Qt6 COMPONENTS DBus Qml Gui REQUIRED)

add_definitions(-DSM_BUSNAME=systemBus)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../../src/liblomiri-private liblomiri-private)

set(APPLICATION_API_INCLUDEDIR /usr/include)
set(LAUNCHER_API_INCLUDEDIR /usr/include)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService
    ${GSETTINGS_QT_INCLUDE_DIRS}
    ${liblomiri-private_SOURCE_DIR}
)

file(GLOB LAUNCHER_SOURCES "*.h" "*.cpp")

qt_add_qml_module(LomiriLauncherAS-qml
    URI Lomiri.Launcher
    VERSION 0.1
    SOURCES
    ${LAUNCHER_SOURCES}
    ../../../AccountsService/AccountsServiceDBusAdaptor.cpp
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationManagerInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/LauncherItemInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/LauncherModelInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/QuickListModelInterface.h
)

target_link_libraries(LomiriLauncherAS-qml
    PRIVATE
    lomiri-private
    ${GSETTINGS_QT_LDFLAGS}
    Qt6::DBus Qt6::Qml Qt6::Gui
    )
