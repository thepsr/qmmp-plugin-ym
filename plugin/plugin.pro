TARGET = ym

UI_DIR=./build/ui/
MOC_DIR=./build/moc/
OBJECTS_DIR=./build/obj

HEADERS += decoderymfactory.h \
           decoder_ym.h \
           digidrum.h \
           LZH.H \
           Ym2149Ex.h \
           YmLoad.h \
           YmMusic.h \
           YmTypes.h

SOURCES += decoder_ym.cpp \
           decoderymfactory.cpp \
           digidrum.cpp \
           LzhLib.cpp \
           Ym2149Ex.cpp \
           YmLoad.cpp \
           YmMusic.cpp

include( ../translations/translations.pri )

CONFIG += release \
warn_on \
plugin 

QMAKE_CXXFLAGS += -Wno-unused-parameter

INCLUDEPATH += /usr/include/qmmp-1

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib

RESOURCES = ../translations/translations.qrc

unix {
    QMAKE_LIBDIR += /usr/lib/qmmp
    LIBS += -lqmmp-1
    QMAKE_CLEAN =./libym.so
}

win32 {
    LIBS += -lqmmp0
}

