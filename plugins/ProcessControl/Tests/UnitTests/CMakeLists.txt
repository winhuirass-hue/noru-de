cmake_minimum_required(VERSION 3.17)
project(ProcessControlTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test DBus Qml)

enable_testing()

add_executable(ProcessControlTest
    tst_processcontrol.cpp
    ../../ProcessControl.cpp
)

target_link_libraries(ProcessControlTest
    PRIVATE
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

add_test(NAME ProcessControl COMMAND ProcessControlTest)
