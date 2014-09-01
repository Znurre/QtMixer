CONFIG += c++11
QT += multimedia
TEMPLATE = lib
DEFINES += QTMIXER_LIBRARY

SOURCES += \
    QAudioDecoderStream.cpp \
    QMixerStream.cpp

HEADERS += \
    QAudioDecoderStream.h \
    QMixerStream.h \
	QMixerStream \
    QtMixer_export.h
