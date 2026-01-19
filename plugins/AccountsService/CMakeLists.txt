cmake_minimum_required(VERSION 3.17)
project(AccountsService-qml LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

add_definitions(-DSM_BUSNAME=systemBus)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)

find_package(Qt6DBus REQUIRED)
find_package(Qt6Qml REQUIRED)

qt_add_qml_module(AccountsService-qml
    URI AccountsService
    VERSION 0.1
    SOURCES
    AccountsService.h
    AccountsService.cpp
    AccountsServiceDBusAdaptor.h
    AccountsServiceDBusAdaptor.cpp
)

target_include_directories(AccountsService-qml
    PRIVATE
    ${GLIB_INCLUDE_DIRS}
)

target_link_libraries(AccountsService-qml
    PRIVATE
    Qt6::DBus Qt6::Qml
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
