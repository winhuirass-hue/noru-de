cmake_minimum_required(VERSION 3.17)
project(AccountsService-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_definitions(-DSM_BUSNAME=systemBus)

set(QT_COMPONENTS DBus Qml)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
    list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp")

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../include/paths.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/paths.h"
)

qt_add_qml_module(AccountsService-qml
    URI AccountsService
    VERSION 0.1
    SOURCES
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(AccountsService-qml
    PRIVATE
    ${GLIB_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(AccountsService-qml
    PRIVATE
    ${QT_LIBS}
    ${GLIB_LIBRARIES}
)

set(DBUS_IFACE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/dbus-1/interfaces")
set(ACCOUNTS_IFACE_DIR "${CMAKE_INSTALL_FULL_DATADIR}/accountsservice/interfaces")

install(FILES com.lomiri.shell.AccountsService.xml
        DESTINATION "${DBUS_IFACE_DIR}"
    )

# Create accountsservice symlink for above dbus interface
install(CODE "
execute_process(COMMAND mkdir -p \"\$ENV{DESTDIR}${ACCOUNTS_IFACE_DIR}\")
execute_process(COMMAND ln -sf ../../dbus-1/interfaces/com.lomiri.shell.AccountsService.xml \"\$ENV{DESTDIR}${ACCOUNTS_IFACE_DIR}\")
    ")
