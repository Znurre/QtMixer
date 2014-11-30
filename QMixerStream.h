#ifndef QMIXERSTREAM_H
#define QMIXERSTREAM_H

#include <QIODevice>
#include <QAudioFormat>

#include "QtMixer.h"
#include "QMixerStreamHandle.h"

typedef std::numeric_limits<qint16> Range;

class QMixerStreamPrivate;

class QTMIXER_EXPORT QMixerStream : public QIODevice
{
	Q_OBJECT

	public:
		QMixerStream(const QAudioFormat &format);

		QMixerStreamHandle openStream(const QString &fileName);

		void closeStream(const QMixerStreamHandle &handle);

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		qint16 mix(qint32 sample1, qint32 sample2);

		QMixerStreamPrivate *d_ptr;

	signals:
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);
		void decodingFinished(QMixerStreamHandle handle);
};

#endif // QMIXERSTREAM_H
