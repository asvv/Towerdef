#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T17:08:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tower_def
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myopenglboard.cpp \
    plain_tower.cpp \
    background.cpp \
    plain_enemy.cpp

HEADERS  += mainwindow.h \
    myopenglboard.h \
    plain_tower.h \
    background.h \
    plain_enemy.h

FORMS    += mainwindow.ui
LIBS += -lopengl32

RESOURCES += \
    shaders.qrc \
    textures.qrc

DISTFILES +=
