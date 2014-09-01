#ifndef QMIXERSTREAM_H
#define QMIXERSTREAM_H

#include <QAudioFormat>
#include <QList>

typedef std::numeric_limits<qint16> Range;

class QMixerStream : public QIODevice
{
	public:
		QMixerStream(const QAudioFormat &format);

		void openStream(QIODevice *device);

	protected:
		qint64 readData(char *data, qint64 maxlen);
		qint64 writeData(const char *data, qint64 len);

	private:
		qint16 mix(qint32 sample1, qint32 sample2);

		QList<QIODevice *> m_streams;
		QAudioFormat m_format;
};

#endif // QMIXERSTREAM_H
