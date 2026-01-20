cmake_minimum_required(VERSION 3.21)
project(UInput-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Qml REQUIRED)

file(GLOB SOURCES "*.cpp" "*.h")

qt_add_qml_module(UInput-qml
    URI UInput
    VERSION 0.1
    SOURCES ${SOURCES}
)

target_link_libraries(UInput-qml PRIVATE Qt6::Qml)

