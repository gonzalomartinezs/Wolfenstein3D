QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coordinate.cpp \
    iconscontainer.cpp \
    item.cpp \
    itemList.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapelement.cpp \
    maphandler.cpp \
    trashbin.cpp

HEADERS += \
    coordinate.h \
    iconscontainer.h \
    item.h \
    itemList.h \
    mainwindow.h \
    map.h \
    mapelement.h \
    maphandler.h \
    trashbin.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    editor.qrc
