cmake_minimum_required(VERSION 3.17)
project(PowerdTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test DBus Qml)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 gio-2.0)

enable_testing()

add_executable(PowerdTest
    tst_powerd.cpp
    ../../Powerd.cpp
)

add_definitions(-DQT_NO_KEYWORDS)

target_include_directories(PowerdTest PRIVATE
    ${GLIB_INCLUDE_DIRS}
)

target_compile_options(PowerdTest PRIVATE
    -Wno-error=unused-parameter
)

target_link_libraries(PowerdTest 
    PRIVATE
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
    ${GLIB_LIBRARIES}
)

add_test(NAME Powerd COMMAND PowerdTest)
