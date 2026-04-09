cmake_minimum_required(VERSION 3.17)

project(InputInfoTests LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test Core Qml)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBUDEV REQUIRED libudev)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
    ${LIBUDEV_INCLUDE_DIRS}
    ${LIBEVDEV_INCLUDE_DIRS}
)

enable_testing()

add_executable(QInputinfoTest
    tst_qinputinfo.cpp
    ../../qinputinfo.cpp
    ../../linux/qinputdeviceinfo_linux.cpp
)

target_link_libraries(QInputinfoTest
    PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Qml
    ${LIBUDEV_LIBRARIES}
    ${LIBEVDEV_LIBRARIES}
)

add_executable(QDeclarativeInputDeviceModelTest
    tst_qdeclarativeinputdevicemodel.cpp
    ../../qinputinfo.cpp
    ../../qdeclarativeinputdevicemodel.cpp
    ../../linux/qinputdeviceinfo_linux.cpp
)

target_link_libraries(QDeclarativeInputDeviceModelTest
    PRIVATE
    Qt6::Test
    Qt6::Core
    Qt6::Qml
    ${LIBUDEV_LIBRARIES}
    ${LIBEVDEV_LIBRARIES}
)

add_test(NAME QInputInfo COMMAND QInputinfoTest)
add_test(NAME QDeclarativeInputDeviceModel COMMAND QDeclarativeInputDeviceModelTest)

