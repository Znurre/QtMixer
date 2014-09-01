#ifndef QMIXERSTREAM_H
#define QMIXERSTREAM_H

#include <QIODevice>
#include <QAudioFormat>
#include <QList>
#include <QAudio>

#include "QtMixer.h"
#include "QMixerStreamHandle.h"

typedef std::numeric_limits<qint16> Range;

class QAbstractMixerStream;

class QTMIXER_EXPORT QMixerStream : public QIODevice
{
	Q_OBJECT

	public:
		QMixerStream(const QAudioFormat &format);

		QMixerStreamHandle openEncodedStream(QIODevice *device);
		QMixerStreamHandle openRawStream(QIODevice *device);

		void closeStream(const QMixerStreamHandle &handle);

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		qint16 mix(qint32 sample1, qint32 sample2);

		QList<QAbstractMixerStream *> m_streams;
		QAudioFormat m_format;

	signals:
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);
};

#endif // QMIXERSTREAM_H
