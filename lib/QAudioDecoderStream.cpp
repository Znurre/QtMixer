#include <QDebug>

#include "QAudioDecoderStream.h"
#include "QMixerStreamHandle.h"

QAudioDecoderStream::QAudioDecoderStream(QIODevice *device, const QAudioFormat &format)
	: m_input(&m_data)
	, m_output(&m_data)
	, m_state(QtMixer::Stopped)
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

	if (m_state == QtMixer::Playing)
	{
		m_output.read(data, maxlen);
	}

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

void QAudioDecoderStream::play()
{
	m_state = QtMixer::Playing;

	emit stateChanged(this, m_state);
}

void QAudioDecoderStream::pause()
{
	m_state = QtMixer::Paused;

	emit stateChanged(this, m_state);
}

void QAudioDecoderStream::stop()
{
	m_state = QtMixer::Stopped;
	m_output.seek(0);

	emit stateChanged(this, m_state);
}

QtMixer::State QAudioDecoderStream::state() const
{
	return m_state;
}
