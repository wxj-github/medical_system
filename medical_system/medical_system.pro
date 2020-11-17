#-------------------------------------------------
#
# Project created by QtCreator 2019-10-21T10:19:38
#
#-------------------------------------------------

QT       += core gui
QT +=sql
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = medical_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    addmedicine.cpp \
    addsales.cpp \
    addcus.cpp \
    readsales.cpp \
    readcus.cpp \
    readmedi.cpp \
    deletemedi.cpp \
    findmedi.cpp \
    changemedi.cpp \
    changesales.cpp \
    changecus.cpp \
    findsales.cpp \
    findcus.cpp \
    deletecus.cpp \
    deletesales.cpp \
    xiugaimima.cpp \
    youke.cpp \
    baobiao.cpp \
    tianjiayonghu.cpp \
    shanchuyonghu.cpp \
    bangzhu.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    addmedicine.h \
    addsales.h \
    addcus.h \
    readsales.h \
    readcus.h \
    readmedi.h \
    deletemedi.h \
    findmedi.h \
    changemedi.h \
    changesales.h \
    changecus.h \
    findsales.h \
    findcus.h \
    deletecus.h \
    deletesales.h \
    xiugaimima.h \
    youke.h \
    baobiao.h \
    tianjiayonghu.h \
    shanchuyonghu.h \
    bangzhu.h

FORMS += \
        mainwindow.ui \
    login.ui \
    addmedicine.ui \
    addsales.ui \
    addcus.ui \
    readsales.ui \
    readcus.ui \
    readmedi.ui \
    deletemedi.ui \
    findmedi.ui \
    changemedi.ui \
    changesales.ui \
    changecus.ui \
    findsales.ui \
    findcus.ui \
    deletecus.ui \
    deletesales.ui \
    xiugaimima.ui \
    youke.ui \
    baobiao.ui \
    tianjiayonghu.ui \
    shanchuyonghu.ui \
    bangzhu.ui

RC_FILE +=cco.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
