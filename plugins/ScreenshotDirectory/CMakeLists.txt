cmake_minimum_required(VERSION 3.17)
project(ScreenshotDirectory-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Qml Quick)

qt_add_qml_module(ScreenshotDirectory-qml
  URI  ScreenshotDirectory
  VERSION 0.1
  SOURCES
  ScreenshotDirectory.h
  ScreenshotDirectory.cpp
)

target_link_libraries(ScreenshotDirectory-qml
  PRIVATE Qt6::Qml Qt6::Gui Qt6::Quick)
