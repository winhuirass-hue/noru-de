cmake_minimum_required(VERSION 3.17)
project(ScreenshotDirectory-qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(QT_COMPONENTS Qml Gui Quick)
set(QT_PACKAGE Qt6)
set(QT_LIBS)
foreach(comp ${QT_COMPONENTS})
  list(APPEND QT_LIBS ${QT_PACKAGE}::${comp})
endforeach()

find_package(${QT_PACKAGE} REQUIRED COMPONENTS ${QT_COMPONENTS})

file(GLOB HEADER_FILES  CONFIGURE_DEPENDS "*.h")
file(GLOB SOURCE_FILES  CONFIGURE_DEPENDS "*.cpp")

qt_add_qml_module(ScreenshotDirectory-qml
  URI  ScreenshotDirectory
  VERSION 0.1
  SOURCES
  ${HEADER_FILES}
  ${SOURCE_FILES}
)

target_link_libraries(ScreenshotDirectory-qml PRIVATE ${QT_LIBS})
