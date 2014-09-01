#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QAudioDecoder>
#include <QBuffer>

#include "MixedStream.h"
#include "DecodingStream.h"

MixedStream::MixedStream()
{

}

void MixedStream::openStream(const QString &fileName)
{
	DecodingStream *stream = new DecodingStream(fileName, m_format);
	stream->open(QIODevice::ReadOnly);

	m_streams << stream;
}

void MixedStream::setFormat(const QAudioFormat &format)
{
	m_format = format;
}

qint64 MixedStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	const qint16 depth = sizeof(qint16);
	const qint16 samples = maxlen / depth;

	QList<QIODevice *> streams = m_streams;

	for (QIODevice *stream : streams)
	{
		qint16 *cursor = (qint16 *)data;
		qint16 sample;

		for (int i = 0; i < samples; i++, cursor++)
		{
			if (stream->read((char *)&sample, depth))
			{
				*cursor = mix(*cursor, sample);
			}
		}

		if (stream->atEnd())
		{
			m_streams.removeOne(stream);

			delete stream;
		}
	}

	return maxlen;
}

qint64 MixedStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

qint16 MixedStream::mix(qint32 sample1, qint32 sample2)
{
	const qint32 result = sample1 + sample2;

	if (Range::max() < result)
	{
		return Range::max();
	}

	if (Range::min() > result)
	{
		return Range::min();
	}

	return result;
}
