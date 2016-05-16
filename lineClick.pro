#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T10:25:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lineClick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linedescriptor.cpp \
    shopform.cpp

HEADERS  += mainwindow.h \
    linedescriptor.h \
    shopform.h

FORMS    += mainwindow.ui \
    shopform.ui

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    main.qrc

