cmake_minimum_required(VERSION 3.16)

project(UInputQMLTests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(appQMLTests
    main.cpp
)

file(GLOB_RECURSE QMLDIR_PATH "${CMAKE_SOURCE_DIR}/../../build/*/qmldir")
if(NOT QMLDIR_PATH)
    if(EXISTS "${CMAKE_SOURCE_DIR}/../../build/qmldir")
        set(QMLDIR_PATH "${CMAKE_SOURCE_DIR}/../../build/qmldir")
    endif()
endif()

if(QMLDIR_PATH)
    get_filename_component(PLUGIN_BUILD_DIR "${QMLDIR_PATH}" DIRECTORY)
    
    set(UINPUT_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/UInput")
    add_custom_command(TARGET appQMLTests PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${UINPUT_MODULE_DIR}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${QMLDIR_PATH}" "${UINPUT_MODULE_DIR}/"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${PLUGIN_BUILD_DIR}/libUInput*" "${UINPUT_MODULE_DIR}/"
    )
    
    target_compile_definitions(appQMLTests PRIVATE PLUGIN_BUILD_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
else()
    message(FATAL_ERROR "UInput plugin not found. Build plugin first: cd ../../ && mkdir build && cd build && cmake .. && make")
endif()

qt_add_qml_module(appQMLTests
    URI QMLTests
    VERSION 1.0
    QML_FILES main.qml 
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQMLTests PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQMLTests
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQMLTests
    PRIVATE Qt6::Quick)

include(GNUInstallDirs)
install(TARGETS appQMLTests
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
