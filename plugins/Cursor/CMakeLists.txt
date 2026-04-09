cmake_minimum_required(VERSION 3.17)
project(Cursor-qml LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
add_subdirectory(3rd_party)

find_package(Qt6Quick REQUIRED)
find_package(Qt6Qml REQUIRED)
find_package(Qt6Svg REQUIRED)

set(APPLICATION_API_INCLUDEDIR "/usr/include")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/xcursor
)

include_directories(
    SYSTEM
    ${Qt6Gui_PRIVATE_INCLUDE_DIRS}
)

qt_add_qml_module(Cursor-qml
  URI Cursor
  VERSION 1.1
  SOURCES
  CursorImageInfo.h
  CursorImageInfo.cpp
  CursorImageProvider.h
  CursorImageProvider.cpp
  MousePointer.h
  MousePointer.cpp
  InputDispatcherFilter.h
  InputDispatcherFilter.cpp
  # We need to run moc on this header
  ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/MirMousePointerInterface.h
)


target_link_libraries(Cursor-qml
    PRIVATE
    xcursorloader-static
    ${QT6PLATFORM_SUPPORT_LDFLAGS}
    Qt6::Qml Qt6::Quick Qt6::Svg
)

