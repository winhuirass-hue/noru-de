cmake_minimum_required(VERSION 3.16)

project(PlatformTests)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core DBus Test Qml REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QTDBUSTEST REQUIRED libqtdbustest-qt6)
pkg_check_modules(QTDBUSMOCK REQUIRED libqtdbusmock-qt6-1)

add_executable(platformtest
    platformtest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../plugins/Lomiri/Platform/platform.cpp
    )

target_include_directories(platformtest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../plugins/Lomiri/Platform
    ${QTDBUSTEST_INCLUDE_DIRS}
    ${QTDBUSMOCK_INCLUDE_DIRS}
)

target_link_libraries(platformtest
    Qt6::Core
    Qt6::DBus
    Qt6::Test
    Qt6::Qml
    ${QTDBUSTEST_LDFLAGS}
    ${QTDBUSMOCK_LDFLAGS}
    )

install(TARGETS platformtest
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/Lomiri/Platform"
)

# Use add_lomiri_unittest when building from root project
# Otherwise fallback to add_test for standalone builds
if(COMMAND add_lomiri_unittest)
    add_lomiri_unittest(Platform qdbus-simple-test-runner
        ARGS $<TARGET_FILE:platformtest>
        )
else()
    set(TEST_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
    set(TEST_ENV "QML2_IMPORT_PATH=${TEST_PROJECT_ROOT}qml:${TEST_PROJECT_ROOT}plugins")
    set(TEST_ENV "${TEST_ENV} LOMIRI_SOURCE_DIR=${TEST_PROJECT_ROOT}")
    enable_testing()
    add_test(NAME PlatformTest
        COMMAND $<TARGET_FILE:platformtest>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set_tests_properties(PlatformTest PROPERTIES ENVIRONMENT "${TEST_ENV}")
endif()
