cmake_minimum_required(VERSION 3.16)
project(LauncherModelASTest)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core DBus Gui Qml Test REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/AccountsService
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/Greeter/Lomiri/Launcher
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService
    ${liblomiri-private_SOURCE_DIR}
)

add_definitions(-DSM_BUSNAME=sessionBus)
add_definitions(-DTEST_DIR="plugins/Greeter/Lomiri/Launcher")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../include/paths.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/paths.h
    @ONLY
)

set(APPLICATION_API_INCLUDEDIR "/usr/include")
set(LAUNCHER_API_INCLUDEDIR "/usr/include")

add_executable(launchermodelastestExec
    launchermodelastest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/AccountsService/AccountsServiceDBusAdaptor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/Greeter/Lomiri/Launcher/launchermodelas.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/Greeter/Lomiri/Launcher/launcheritem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/Greeter/Lomiri/Launcher/quicklistmodel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../plugins/Greeter/Lomiri/Launcher/quicklistentry.cpp
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/LauncherItemInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/LauncherModelInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/launcher/QuickListModelInterface.h
    ${APPLICATION_API_INCLUDEDIR}/lomiri/shell/application/ApplicationManagerInterface.h
    ${LAUNCHER_API_INCLUDEDIR}/lomiri/shell/application/ApplicationInfoInterface.h
)
target_link_libraries(launchermodelastestExec
    lomiri-private
    ${GSETTINGS_QT_LDFLAGS}
    Qt6::Test Qt6::Core Qt6::DBus Qt6::Gui Qt6::Qml
)

add_dependencies(launchermodelastestExec mock-server)

install(TARGETS launchermodelastestExec
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/Greeter/Lomiri/Launcher"
)

# Use add_lomiri_unittest when building from root project
# Otherwise fallback to add_test for standalone builds
if(COMMAND add_lomiri_unittest)
    add_lomiri_unittest(LauncherModelAS dbus-test-runner
        ARG_PREFIX "--parameter"
        ARGS
        --task $<TARGET_FILE:mock-server>
        --ignore-return
        --task $<TARGET_FILE:launchermodelastestExec>
        --wait-for org.freedesktop.Accounts
    )

else()

    find_program(QDBUSXML2CPP_EXECUTABLE qdbusxml2cpp REQUIRED)

    macro(make_dbus_class NAME INTERFACE)
        if(${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/interfaces.xml IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor.h)
            execute_process(COMMAND ${QDBUSXML2CPP_EXECUTABLE} -c ${NAME}Adaptor -i types.h -a ${CMAKE_CURRENT_BINARY_DIR}/${NAME}Adaptor ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/interfaces.xml ${INTERFACE}
                OUTPUT_QUIET ERROR_QUIET)
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
    
    add_executable(mock-server
        ${CMAKE_CURRENT_BINARY_DIR}/AccountsAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/AccountsPrivateAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/AccountsUserAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/InputAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/PropertiesAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/LocationAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/SecurityPrivacyAdaptor.cpp
        ${CMAKE_CURRENT_BINARY_DIR}/LscInputAdaptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/server.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/AccountsServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/PropertiesServer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../AccountsService/LscServer.cpp
    )
target_link_libraries(mock-server Qt6::Core Qt6::DBus Qt6::Qml)

install(TARGETS mock-server
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/Greeter/Lomiri/Launcher"
)

set(TEST_PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../")

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/run-test.sh.in" "#!/bin/bash\nexport QML2_IMPORT_PATH=@TEST_PROJECT_ROOT@qml:@TEST_PROJECT_ROOT@plugins\nexport LOMIRI_SOURCE_DIR=@TEST_PROJECT_ROOT@\n@CMAKE_CURRENT_BINARY_DIR@/mock-server &\nMOCK_PID=$!\nsleep 1\n@CMAKE_CURRENT_BINARY_DIR@/launchermodelastestExec\nRESULT=$?\nkill $MOCK_PID 2>/dev/null || true\nwait $MOCK_PID 2>/dev/null || true\nexit $RESULT\n")
    
    configure_file(
        "${CMAKE_CURRENT_BINARY_DIR}/run-test.sh.in"
        "${CMAKE_CURRENT_BINARY_DIR}/run-test.sh"
        @ONLY
    )

execute_process(COMMAND chmod +x "${CMAKE_CURRENT_BINARY_DIR}/run-test.sh")

enable_testing()
add_test(NAME LauncherModelASTest
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/run-test.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
endif()


