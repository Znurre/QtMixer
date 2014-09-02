CONFIG += c++11
QT += multimedia
TEMPLATE = lib
DEFINES += QTMIXER_LIBRARY

SOURCES += \
    QAudioDecoderStream.cpp \
    QMixerStream.cpp \
    QMixerStreamHandle.cpp \
    QMixerStream_p.cpp

HEADERS += \
    QAudioDecoderStream.h \
	QMixerStream.h \
    QMixerStreamHandle.h \
    QAbstractMixerStream.h \
	QtMixer.h \
    QMixerStream_p.h

OTHER_FILES += \
	QMixerStream \
	QMixerStreamHandle
