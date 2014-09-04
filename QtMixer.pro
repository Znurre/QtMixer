CONFIG += c++11 plugin
QT += multimedia
TEMPLATE = lib
DEFINES += QTMIXER_LIBRARY
TARGET = $$qtLibraryTarget(QtMixer)

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
	QMixerStreamHandle \
    mixer.prf

headers.files = QMixerStream.h QMixerStream	QMixerStreamHandle.h QMixerStreamHandle	QtMixer.h
headers.path = $$[QT_INSTALL_HEADERS]/QtMixer

libs.files = libQtMixer.so
libs.path = $$[QT_INSTALL_LIBS]

features.files = mixer.prf
features.path = $$[QMAKE_MKSPECS]/features

INSTALLS += headers libs features
