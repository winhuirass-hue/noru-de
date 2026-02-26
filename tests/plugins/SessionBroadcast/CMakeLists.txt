cmake_minimum_required(VERSION 3.16)
project(SessionBroadcastTests)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core DBus Test Qml REQUIRED)
include(FindPkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)

find_program(QDBUSXML2CPP_EXECUTABLE qdbusxml2cpp REQUIRED)

macro(make_dbus_class NAME INTERFACE)
    if(${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor.h)
        execute_process(COMMAND ${QDBUSXML2CPP_EXECUTABLE} -c ${NAME}Adaptor -a ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor ${CMAKE_CURRENT_SOURCE_DIR}/interfaces.xml ${INTERFACE})
    endif()
endmacro(make_dbus_class)

make_dbus_class(Broadcast com.lomiri.Shell.Greeter.Broadcast)

# Qt6 fix: Remove QStringList forward declaration (it's a using alias in Qt6, not a class)
file(GLOB GENERATED_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/*Adaptor.h")
foreach(HEADER ${GENERATED_HEADERS})
    file(READ "${HEADER}" CONTENT)
    string(REGEX REPLACE "class QStringList;" "" CONTENT "${CONTENT}")
    file(WRITE "${HEADER}" "${CONTENT}")
endforeach()

add_definitions(-DSM_BUSNAME=sessionBus)

include_directories(
    ${GLIB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/SessionBroadcast
)

link_libraries(
    ${GLIB_LIBRARIES}
)

add_executable(MockBroadcastServer
    ${CMAKE_CURRENT_BINARY_DIR}/BroadcastAdaptor.cpp
    server.cpp
    BroadcastServer.cpp
)
target_link_libraries(MockBroadcastServer Qt6::Core Qt6::DBus Qt6::Qml)
install(TARGETS MockBroadcastServer
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/SessionBroadcast"
)

### SessionBroadcastTest
add_executable(sessionbroadcasttestExec
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/SessionBroadcast/SessionBroadcast.cpp
    sessionbroadcasttest.cpp
)
target_link_libraries(sessionbroadcasttestExec Qt6::Test Qt6::Core Qt6::Qml Qt6::DBus)
install(TARGETS sessionbroadcasttestExec
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/SessionBroadcast"
)

# Use add_lomiri_unittest when building from root project
# Otherwise fallback to add_test for standalone builds
if(COMMAND add_lomiri_unittest)
    add_lomiri_unittest(SessionBroadcast dbus-test-runner
        ARG_PREFIX "--parameter"
        ARGS
            --task $<TARGET_FILE:MockBroadcastServer>
            --task-name server
            --ignore-return
            --task $<TARGET_FILE:sessionbroadcasttestExec>
            --task-name client
            --wait-for com.lomiri.Shell.Greeter.Broadcast
    )
else()
    set(TEST_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../")
    enable_testing()
    add_test(NAME SessionBroadcastTest
        COMMAND dbus-test-runner
            --task $<TARGET_FILE:MockBroadcastServer>
            --task-name server
            --ignore-return
            --task $<TARGET_FILE:sessionbroadcasttestExec>
            --task-name client
            --wait-for com.lomiri.Shell.Greeter.Broadcast
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    set_tests_properties(SessionBroadcastTest PROPERTIES
        ENVIRONMENT "QML2_IMPORT_PATH=${TEST_PROJECT_ROOT}qml:${TEST_PROJECT_ROOT}plugins;LOMIRI_SOURCE_DIR=${TEST_PROJECT_ROOT}"
    )
endif()
