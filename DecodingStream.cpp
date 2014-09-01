#include <QDebug>

#include "DecodingStream.h"

DecodingStream::DecodingStream(const QString &fileName, const QAudioFormat &format)
	: m_input(&m_data)
	, m_output(&m_data)
	, m_file(fileName)
	, m_atEnd(false)
{
	m_input.open(QIODevice::WriteOnly);
	m_output.open(QIODevice::ReadOnly);
	m_file.open(QIODevice::ReadOnly);

	m_decoder.setAudioFormat(format);
	m_decoder.setSourceDevice(&m_file);
	m_decoder.start();

	connect(&m_decoder, &QAudioDecoder::bufferReady, this, &DecodingStream::bufferReady);
}

qint64 DecodingStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	m_output.read(data, maxlen);

	return maxlen;
}

qint64 DecodingStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

void DecodingStream::bufferReady()
{
	QAudioBuffer buffer = m_decoder.read();

	int length = buffer.byteCount();
	char *data = buffer.data<char>();

	m_input.write(data, length);
}

bool DecodingStream::atEnd() const
{
	return m_data.length() && m_output.atEnd();
}
