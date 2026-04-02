# This is a temporary snapshot of the WIP QInputInfo API as we
# require this in lomiri now but upstream isn't finished yet.
# Eventually this should be dropped in favor of the upstream
# QInputInfo API.

cmake_minimum_required(VERSION 3.17)
project(InputInfo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS Core Quick Qml)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUDEV REQUIRED libudev)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${LIBUDEV_INCLUDE_DIRS}
    ${LIBEVDEV_INCLUDE_DIRS}
)

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h" "linux/*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp" "linux/*.cpp")

qt_add_qml_module(InputInfo
    URI Lomiri.InputInfo
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_link_libraries(InputInfo
    PRIVATE
    ${LIBUDEV_LDFLAGS}
    ${LIBEVDEV_LDFLAGS}
    ${QT_LIBS}
)

