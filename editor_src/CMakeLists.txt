cmake_minimum_required(VERSION 3.5)

project(Editor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

#pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

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
        iconsPaths.h
        ../common_src/GameConstants.h InvalidFileException.cpp InvalidFileException.h MessageBox.cpp MessageBox.h EditorIcon.h)

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
target_link_libraries(Editor PRIVATE ${YAMLCPP_LIBRARIES})

install(TARGETS Editor
    RUNTIME DESTINATION "/usr/bin/")

install(DIRECTORY "icons"
    DESTINATION "/usr/games/Wolfenstein3D"
    COMPONENT Editor)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_NAME "Wolfenstein3DEditor")
set(CPACK_PACKAGE_FILE_NAME "W3DEditor")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Grupo 4 - Taller - 2c2020")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION "Wolfenstein3D map editor.")
set(CPACK_PACKAGE_ICON "logo.png")

install(FILES executable/logo.png DESTINATION share/icons/Wolfenstein3D/ COMPONENT Editor)
install(FILES executable/Editor.desktop DESTINATION /usr/share/applications/ COMPONENT Editor) 

INCLUDE(CPack)