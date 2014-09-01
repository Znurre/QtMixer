CONFIG += c++11
QT += multimedia
TEMPLATE = lib
DEFINES += QTMIXER_LIBRARY

SOURCES += \
    QAudioDecoderStream.cpp \
    QMixerStream.cpp \
    QMixerStreamHandle.cpp \
    QMixerWrapperStream.cpp

HEADERS += \
    QAudioDecoderStream.h \
    QMixerStream.h \
	QMixerStream \
    QMixerStreamHandle.h \
    QMixerWrapperStream.h \
    QAbstractMixerStream.h \
    QtMixer.h
