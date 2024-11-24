QT       += core gui
QT       += sql
QT       += printsupport
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    base_view.cpp \
    del.cpp \
    dobav.cpp \
    main.cpp \
    mainwindow.cpp \
    obnova.cpp \
    regist.cpp \
    test.cpp

HEADERS += \
    base_view.h \
    del.h \
    dobav.h \
    mainwindow.h \
    obnova.h \
    regist.h \
    test.h \
    testUnit.h

FORMS += \
    base_view.ui \
    del.ui \
    dobav.ui \
    mainwindow.ui \
    obnova.ui \
    regist.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
