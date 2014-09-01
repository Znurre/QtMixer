#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QAudioDecoder>
#include <QBuffer>

#include "QMixerStream.h"
#include "QAudioDecoderStream.h"

QMixerStream::QMixerStream(const QAudioFormat &format)
	: m_format(format)
{

}

void QMixerStream::openStream(QIODevice *device)
{
	m_streams << new QAudioDecoderStream(device, m_format);
}

qint64 QMixerStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	const qint16 depth = sizeof(qint16);
	const qint16 samples = maxlen / depth;

	const QList<QIODevice *> streams = m_streams;

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

qint64 QMixerStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

qint16 QMixerStream::mix(qint32 sample1, qint32 sample2)
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
