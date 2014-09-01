#ifndef MIXEDSTREAM_H
#define MIXEDSTREAM_H

#include <QAudioFormat>
#include <QIODevice>
#include <QList>

using Range = std::numeric_limits<qint16>;

class MixedStream : public QIODevice
{
	public:
		MixedStream();

		void openStream(const QString &fileName);
		void setFormat(const QAudioFormat &format);

		// QIODevice interface
	protected:
		qint64 readData(char *data, qint64 maxlen);
		qint64 writeData(const char *data, qint64 len);

	private:
		qint16 mix(qint32 sample1, qint32 sample2);

		QList<QIODevice *> m_streams;
		QAudioFormat m_format;
};

#endif // MIXEDSTREAM_H
