cmake_minimum_required(VERSION 3.17)
project(ModemConnectivityTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
    DBus
    Qml
)

add_executable(tst_modemconnectivity
    tst_modemconnectivity.cpp
    ../../ModemConnectivity.cpp
)

target_link_libraries(tst_modemconnectivity PRIVATE
    Qt6::Core
    Qt6::Test
    Qt6::DBus
    Qt6::Qml
)

target_include_directories(tst_modemconnectivity PRIVATE
    ../../
)

enable_testing()
add_test(NAME ModemConnectivityTest COMMAND tst_modemconnectivity)

set_target_properties(tst_modemconnectivity PROPERTIES
    BUILD_RPATH "$ORIGIN"
)
