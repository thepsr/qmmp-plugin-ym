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

INCLUDEPATH += /usr/include/
CONFIG += release \
warn_on \
plugin 

QMAKE_CXXFLAGS += -Wno-unused-parameter

TEMPLATE = lib

RESOURCES = ../translations/translations.qrc

unix {
    LIBS += -lqmmp
    QMAKE_CLEAN =./libym.so
}

win32 {
    LIBS += -lqmmp0
}

