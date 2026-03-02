cmake_minimum_required(VERSION 3.17)
project(UInputTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test Qml)

enable_testing()

add_executable(UInputTest
    tst_uinput.cpp
    ../../uinput.cpp
)

target_link_libraries(UInputTest 
    PRIVATE
    Qt6::Test
    Qt6::Qml
)

add_test(NAME UInput COMMAND UInputTest)
