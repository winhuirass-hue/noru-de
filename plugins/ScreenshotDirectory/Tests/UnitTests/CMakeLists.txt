cmake_minimum_required(VERSION 3.17)
project(ScreenshotDirectoryTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test Core Qml)

enable_testing()

add_executable(ScreenshotDirectoryTest
    tst_screenshotdirectory.cpp
    ../../ScreenshotDirectory.cpp
)

target_include_directories(ScreenshotDirectoryTest
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(ScreenshotDirectoryTest
    PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Qml
)

add_test(
    NAME ScreenshotDirectory
    COMMAND ScreenshotDirectoryTest -v2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

set_tests_properties(ScreenshotDirectory PROPERTIES
    ENVIRONMENT "LOMIRI_TESTING=1"
)
