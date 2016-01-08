#-------------------------------------------------
#
# Project created by QtCreator 2016-01-05T18:02:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOS
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mydispatchview.cpp \
    mymemoryview.cpp \
    mydispatchmode.cpp \
    mymemorymode.cpp \
    myfile.cpp \
    myfilemode.cpp \
    mytextedit.cpp

HEADERS  += widget.h \
    mydispatchview.h \
    mymemoryview.h \
    mydispatchmode.h \
    mymemorymode.h \
    myfile.h \
    myfilemode.h \
    mytextedit.h

FORMS    += \
    mydispatchview.ui \
    mymemoryview.ui \
    myfile.ui

RESOURCES += \
    resource.qrc
