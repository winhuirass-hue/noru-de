cmake_minimum_required(VERSION 3.16)

project(DownloadTrackerTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
    DBus
    Qml
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DDLADAPTER REQUIRED ldm-common-qt6)
list(FILTER DDLADAPTER_LIBRARIES EXCLUDE REGEX "^Qt6")

add_definitions(${DDLADAPTER_CFLAGS} ${DDLADAPTER_CFLAGS_OTHER})

add_executable(tst_downloadtracker
    tst_downloadtracker.cpp
    ../../DownloadTracker.cpp
    ../../interface/downloadtrackeradaptor.cpp
)

target_link_libraries(tst_downloadtracker PRIVATE
    Qt6::Core
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
    ${DDLADAPTER_LIBRARIES}
)

target_include_directories(tst_downloadtracker PRIVATE
    ../../
    ../../interface
    ${DDLADAPTER_INCLUDE_DIRS}
)

enable_testing()
add_test(NAME DownloadTrackerTest COMMAND tst_downloadtracker)

set_target_properties(tst_downloadtracker PROPERTIES BUILD_RPATH "${DDLADAPTER_LIBRARY_DIRS}")
