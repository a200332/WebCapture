#-------------------------------------------------
#
# Project created by QtCreator 2011-10-29T12:56:02
#
#-------------------------------------------------

QT       += core gui thread network sql

TARGET = WebCapture
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    manager.cpp \
    downunit.cpp \
    processthread.cpp \
    orderbuilder.cpp \
    txtfilebuilder.cpp \
    savebysqlite.cpp \
    SavePolicy.cpp

HEADERS  += mainwidget.h \
    manager.h \
    downunit.h \
    myutil.h \
    processthread.h \
    urlbuilder.h \
    orderbuilder.h \
    txtfilebuilder.h \
    savepolicy.h \
    savebysqlite.h

FORMS    += mainwidget.ui





