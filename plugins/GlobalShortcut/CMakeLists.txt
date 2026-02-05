cmake_minimum_required(VERSION 3.24)
project(GlobalShortcut-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Quick Gui REQUIRED)

file(GLOB GLOBALSHORTCUT_FILES "*.h" "*.cpp")

qt_add_qml_module(GlobalShortcut-qml
    URI GlobalShortcut
    VERSION 1.0
    SOURCES
    ${GLOBALSHORTCUT_FILES}
)

target_link_libraries(GlobalShortcut-qml PRIVATE Qt6::Quick Qt6::Gui)

