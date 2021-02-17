cmake_minimum_required(VERSION 3.5)

project(Editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        coordinate.cpp
        coordinate.h
        iconscontainer.cpp
        iconscontainer.h
        itemList.cpp
        itemList.h
        map.cpp
        map.h
        mapelement.cpp
        mapelement.h
        maphandler.cpp
        maphandler.h
        mapparser.cpp
        mapparser.h
        trashbin.h
        trashbin.cpp
        icons/iconsPaths.h
        ../common_src/GameConstants.h)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Editor
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Editor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Editor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Editor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
