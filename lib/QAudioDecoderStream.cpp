#include <QDebug>

#include "QAudioDecoderStream.h"

QAudioDecoderStream::QAudioDecoderStream(QIODevice *device, const QAudioFormat &format)
	: m_input(&m_data)
	, m_output(&m_data)
{
	setOpenMode(QIODevice::ReadOnly);

	m_input.open(QIODevice::WriteOnly);
	m_output.open(QIODevice::ReadOnly);

	m_decoder.setAudioFormat(format);
	m_decoder.setSourceDevice(device);
	m_decoder.start();

	connect(&m_decoder, &QAudioDecoder::bufferReady, this, &QAudioDecoderStream::bufferReady);
}

qint64 QAudioDecoderStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	m_output.read(data, maxlen);

	return maxlen;
}

qint64 QAudioDecoderStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

void QAudioDecoderStream::bufferReady()
{
	const QAudioBuffer &buffer = m_decoder.read();

	const int length = buffer.byteCount();
	const char *data = buffer.data<char>();

	m_input.write(data, length);
}

bool QAudioDecoderStream::atEnd() const
{
	return m_output.bytesAvailable()
		&& m_output.atEnd();
}
