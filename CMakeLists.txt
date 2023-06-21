cmake_minimum_required(VERSION 3.5)

project(calc_2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_SOURCE_DIR}/ui
${CMAKE_CURRENT_SOURCE_DIR}/source
${CMAKE_CURRENT_SOURCE_DIR}/headers
)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

set(PROJECT_SOURCES
    source/main.cpp
            source/mainwindow.cpp
            headers/mainwindow.h
            source/qcustomplot.cpp
            headers/qcustomplot.h
            ui/mainwindow.ui
            source/chart.cpp
            headers/chart.h
            ui/chart.ui
            source/c_libs.c
            headers/c_libs.h
            ui/deposit_form.ui
            source/deposit_form.cpp
            headers/deposit_form.h
            source/credit.cpp
            headers/credit.h
            ui/credit.ui



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calc_2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calc_2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(calc_2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calc_2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(calc_2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(calc_2 PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)
set_target_properties(calc_2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calc_2)
endif()
