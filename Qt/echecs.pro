QT       += core gui widgets
CONFIG   += c++17
TARGET    = echecs
TEMPLATE  = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    echiquierwidget.cpp \
    ../plateau.cpp

HEADERS += \
    mainwindow.h \
    echiquierwidget.h \
    ../plateau.h
