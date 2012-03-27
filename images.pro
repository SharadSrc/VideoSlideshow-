#-------------------------------------------------
#
# Project created by QtCreator 2010-12-19T17:38:31
#
#-------------------------------------------------

QT       += core gui phonon

TARGET = mvd
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp \
    sequencemodel.cpp \
    node.cpp \
    delegate.cpp \
    nodepropertiesdialog.cpp \
    effect.cpp \
    slideshowengine.cpp \
    moviepropertiesdialog.cpp \
    soundtracksdialog.cpp \
    soundengine.cpp

HEADERS  += mainwindow.h \
    sequencemodel.h \
    node.h \
    pixmap.h \
    delegate.h \
    nodepropertiesdialog.h \
    effect.h \
    slideshowengine.h \
    moviepropertiesdialog.h \
    const.h \
    soundtracksdialog.h

FORMS    += mainwindow.ui \
    nodepropertiesdialog.ui \
    moviepropertiesdialog.ui \
    soundtracksdialog.ui

RESOURCES += \
    images.qrc \
    images.qrc

