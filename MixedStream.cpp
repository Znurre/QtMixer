#include <QFile>
#include <QDebug>
#include <QByteArray>

#include "MixedStream.h"

MixedStream::MixedStream()
{

}

void MixedStream::openStream(const QString &fileName)
{
	QFile *file = new QFile(fileName);

	if (file->open(QIODevice::ReadOnly))
	{
		m_streams << file;

		qDebug() << "Opened stream for" << fileName;
	}
	else
	{
		qDebug() << "Failed to open stream for" << fileName;

		delete file;
	}
}

qint64 MixedStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	qint16 depth = sizeof(qint16);
	qint16 samples = maxlen / depth;

	QList<QIODevice *> streams = m_streams;

	for (QIODevice *stream : streams)
	{
		qint16 *cursor = (qint16 *)data;
		qint16 sample;

		for (int i = 0; i < samples; i++)
		{
			if (stream->read((char *)&sample, depth))
			{
				*(cursor++) += sample / CHANNELS;
			}
		}

		if (stream->atEnd())
		{
			qDebug() << "end of stream";

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
