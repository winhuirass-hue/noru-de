cmake_minimum_required(VERSION 3.17)
project(GlobalShortcutTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Test Quick Qml Gui REQUIRED)
include(FindPkgConfig)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/GlobalShortcut
)

add_definitions(-DTEST_DIR="plugins/GlobalShortcut")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/paths.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/paths.h
    @ONLY
)

qt_add_executable(GlobalShortcutTestExec
    GlobalShortcutTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/GlobalShortcut/globalshortcut.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/GlobalShortcut/globalshortcutregistry.cpp
)
target_link_libraries(GlobalShortcutTestExec  PRIVATE Qt6::Test Qt6::Quick Qt6::Qml Qt6::Gui)

install(TARGETS GlobalShortcutTestExec
    DESTINATION "${SHELL_PRIVATE_LIBEXECDIR}/tests/plugins/GlobalShortcut"
)
install(FILES shortcut.qml
    DESTINATION "${SHELL_APP_DIR}/tests/plugins/GlobalShortcut"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../../plugins/GlobalShortcut
                 ${CMAKE_CURRENT_BINARY_DIR}/plugins/GlobalShortcut)

enable_testing()

# Use add_lomiri_uitest when building from root project
# Otherwise fallback to add_test for standalone builds
if(COMMAND add_lomiri_uitest)
    add_lomiri_uitest(GlobalShortcut GlobalShortcutTestExec
        DEPENDS GlobalShortcut-qml
        ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/plugins/GlobalShortcut
    )
else()
    add_test(
        NAME GlobalShortcutTest
        COMMAND GlobalShortcutTestExec
    )
    set_tests_properties(GlobalShortcutTest PROPERTIES
        ENVIRONMENT "LOMIRI_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/../../../;LOMIRI_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}/../../../;QML2_IMPORT_PATH=${CMAKE_CURRENT_BINARY_DIR}/plugins;QT_QPA_PLATFORM=xcb"
    )
    add_dependencies(GlobalShortcutTestExec GlobalShortcut-qml)
endif()
