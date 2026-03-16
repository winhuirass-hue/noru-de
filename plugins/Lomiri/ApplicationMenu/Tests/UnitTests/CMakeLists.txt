cmake_minimum_required(VERSION 3.17)
project(ApplicationMenuTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test DBus Qml)
find_program(QDBUSXML2CPP_EXECUTABLE qdbusxml2cpp REQUIRED)

enable_testing()

execute_process(
    COMMAND ${QDBUSXML2CPP_EXECUTABLE}
    -c MenuRegistrarAdaptor
    -a ${CMAKE_CURRENT_BINARY_DIR}/menuregistraradaptor
    ${CMAKE_CURRENT_SOURCE_DIR}/../../com.lomiri.MenuRegistrar.xml
    com.lomiri.MenuRegistrar
    RESULT_VARIABLE QDBUSXML2CPP_RESULT
)

if(NOT QDBUSXML2CPP_RESULT EQUAL 0)
    message(FATAL_ERROR "qdbusxml2cpp failed to generate adaptor")
endif()

# In Qt6, QStringList is a using alias, not a class declaration
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/menuregistraradaptor.h)
    file(READ ${CMAKE_CURRENT_BINARY_DIR}/menuregistraradaptor.h ADAPTOR_HEADER_CONTENT)
    string(REPLACE
        "class QStringList;"
        "// QStringList is a using alias in Qt6, not a class"
        ADAPTOR_HEADER_CONTENT
        "${ADAPTOR_HEADER_CONTENT}"
    )
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/menuregistraradaptor.h "${ADAPTOR_HEADER_CONTENT}")
endif()

add_executable(MenuServicePathTest
    tst_menuservicepath.cpp
    ../../applicationmenuregistry.cpp
)

target_include_directories(MenuServicePathTest 
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(MenuServicePathTest 
    PRIVATE
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

add_test(NAME MenuServicePath COMMAND MenuServicePathTest)

add_executable(ApplicationMenuRegistryTest
    tst_applicationmenuregistry.cpp
    ../../applicationmenuregistry.cpp
    ../../dbusapplicationmenuregistry.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/menuregistraradaptor.cpp
)

target_include_directories(ApplicationMenuRegistryTest 
    PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_link_libraries(ApplicationMenuRegistryTest 
    PRIVATE
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

add_test(NAME ApplicationMenuRegistry COMMAND ApplicationMenuRegistryTest)
