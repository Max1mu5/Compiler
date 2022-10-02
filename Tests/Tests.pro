QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

SOURCES +=  tst_performance.cpp \
    ../Code/lexicalwindow.cpp \
    ../Code/mainwindow.cpp

SUBDIRS += \
    ../Code/Compiler.pro

FORMS += \
    ../Code/lexicalwindow.ui \
    ../Code/mainwindow.ui

HEADERS += \
    ../Code/lexicalwindow.h \
    ../Code/mainwindow.h
