QT += core gui sql charts widgets

TARGET = LOGAI
TEMPLATE = app

SOURCES += main.cpp \
    src/mainwindow.cpp \
    src/db/databasemanager.cpp \
    src/thread/logparserthread.cpp \
    src/chart/chartmanager.cpp \
    src/logmodel.cpp

HEADERS += src/mainwindow.h \
    src/db/databasemanager.h \
    src/thread/logparserthread.h \
    src/chart/chartmanager.h \
    src/logmodel.h

FORMS += src/mainwindow.ui

RESOURCES += 

DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc
