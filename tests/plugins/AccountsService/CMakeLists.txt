cmake_minimum_required(VERSION 3.17)
project(AccountsServiceTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core DBus Test Qml REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

find_program(QDBUSXML2CPP_EXECUTABLE qdbusxml2cpp REQUIRED)

macro(make_dbus_class NAME INTERFACE)
    if(${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor.h)
        execute_process(COMMAND ${QDBUSXML2CPP_EXECUTABLE} -c ${NAME}Adaptor -i types.h -a ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor ${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml ${INTERFACE})
    endif()
endmacro(make_dbus_class)

make_dbus_class(Accounts org.freedesktop.Accounts)
make_dbus_class(Input com.lomiri.AccountsService.Input)
make_dbus_class(Properties org.freedesktop.DBus.Properties)
make_dbus_class(SecurityPrivacy com.lomiri.touch.AccountsService.SecurityPrivacy)
make_dbus_class(Location com.ubuntu.location.providers.here.AccountsService)
make_dbus_class(AccountsUser org.freedesktop.Accounts.User)
make_dbus_class(AccountsPrivate com.lomiri.shell.AccountsService.Private)
make_dbus_class(LscInput com.lomiri.SystemCompositor.Input)

file(GLOB GENERATED_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/*Adaptor.h")
foreach(HEADER ${GENERATED_HEADERS})
    file(READ "${HEADER}" CONTENT)
    string(REGEX REPLACE "class QStringList;" "" CONTENT "${CONTENT}")
    file(WRITE "${HEADER}" "${CONTENT}")
endforeach()

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../include/paths.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/paths.h"
)

include_directories(
    ${GLIB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/AccountsService
)

link_libraries(
    ${GLIB_LIBRARIES}
)

add_definitions(-DSM_BUSNAME=sessionBus)

add_executable(mock-server
    ${CMAKE_CURRENT_BINARY_DIR}/AccountsAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/AccountsPrivateAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/AccountsUserAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/InputAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/PropertiesAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/LocationAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/SecurityPrivacyAdaptor.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/LscInputAdaptor.cpp
    server.cpp
    AccountsServer.cpp
    PropertiesServer.cpp
    LscServer.cpp
    )
target_link_libraries(mock-server Qt6::Core Qt6::DBus Qt6::Qml)
install(TARGETS mock-server
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/AccountsService"
)

add_executable(test-accountsservice
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/AccountsService/AccountsService.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    client.cpp
    )
target_link_libraries(test-accountsservice Qt6::Core Qt6::DBus Qt6::Test Qt6::Qml)
install(TARGETS test-accountsservice
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/AccountsService"
)

# Use add_lomiri_unittest when building from root project
# Otherwise fallback to add_test for standalone builds
if(COMMAND add_lomiri_unittest)
    add_lomiri_unittest(AccountsService dbus-test-runner
        ARG_PREFIX "--parameter"
        ARGS
            --task $<TARGET_FILE:mock-server>
            --task-name server
            --ignore-return
            --task $<TARGET_FILE:test-accountsservice>
            --task-name client
            --wait-for org.freedesktop.Accounts
    )
else()
    set(TEST_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
    enable_testing()
    add_test(NAME AccountsServiceTest
        COMMAND /usr/bin/dbus-test-runner
            --task $<TARGET_FILE:mock-server>
            --task-name server
            --ignore-return
            --task $<TARGET_FILE:test-accountsservice>
            --task-name client
            --wait-for org.freedesktop.Accounts
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set_tests_properties(AccountsServiceTest PROPERTIES
        ENVIRONMENT "QML2_IMPORT_PATH=${TEST_PROJECT_ROOT}qml:${TEST_PROJECT_ROOT}plugins;LOMIRI_SOURCE_DIR=${TEST_PROJECT_ROOT}"
    )
endif()
