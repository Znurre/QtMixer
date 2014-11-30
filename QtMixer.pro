CONFIG += c++11
QT += multimedia
TEMPLATE = lib
DEFINES += QTMIXER_LIBRARY
TARGET = $$qtLibraryTarget(QtMixer)
VER_MAJ = 2

SOURCES += \
	QAudioDecoderStream.cpp \
	QMixerStream.cpp \
	QMixerStreamHandle.cpp \
	QMixerStream_p.cpp

INSTALL_HEADERS += \
	QMixerStream.h \
	QMixerStreamHandle.h \
	QtMixer.h \
	QMixerStream \
	QMixerStreamHandle

PRIVATE_HEADERS += \
	QAudioDecoderStream.h \
	QAbstractMixerStream.h \
	QMixerStream_p.h

HEADERS = \
	$${INSTALL_HEADERS} \
	$${PRIVATE_HEADERS}

OTHER_FILES += \
	mixer.prf

headers.files = $${INSTALL_HEADERS}
headers.path = $$[QT_INSTALL_HEADERS]/QtMixer

target.path = $$[QT_INSTALL_LIBS]

features.files = mixer.prf
features.path = $$[QMAKE_MKSPECS]/features

INSTALLS += headers target features
