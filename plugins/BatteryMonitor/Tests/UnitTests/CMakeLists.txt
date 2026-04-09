cmake_minimum_required(VERSION 3.17)
project(BatteryMonitorTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test DBus Qml)

enable_testing()

add_executable(BatteryMonitorTest
    tst_batterymonitor.cpp
    ../../BatteryMonitor.cpp
)

target_link_libraries(BatteryMonitorTest 
    PRIVATE
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

add_test(NAME BatteryMonitor COMMAND BatteryMonitorTest)
