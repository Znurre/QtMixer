#include <QDebug>

#include "QAudioDecoderStream.h"
#include "QMixerStreamHandle.h"

QAudioDecoderStream::QAudioDecoderStream(const QString &fileName, const QAudioFormat &format)
	: m_file(fileName)
	, m_input(&m_data)
	, m_output(&m_data)
	, m_format(format)
	, m_state(QtMixer::Stopped)
	, m_loops(0)
	, m_remainingLoops(0)
{
	setOpenMode(QIODevice::ReadOnly);

	const bool valid =
		m_file.open(QIODevice::ReadOnly) &&
		m_output.open(QIODevice::ReadOnly) &&
		m_input.open(QIODevice::WriteOnly);

	Q_ASSERT(valid);

	m_decoder.setNotifyInterval(10);
	m_decoder.setAudioFormat(format);
	m_decoder.setSourceDevice(&m_file);
	m_decoder.start();

	connect(&m_decoder, &QAudioDecoder::bufferReady, this, &QAudioDecoderStream::bufferReady);
	connect(&m_decoder, &QAudioDecoder::finished, this, &QAudioDecoderStream::finished);
}

qint64 QAudioDecoderStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	if (m_state == QtMixer::Playing)
	{
		m_output.read(data, maxlen);

		if (m_output.size() &&
			m_output.atEnd())
		{
			if (m_loops != 0)
			{
				if (m_loops > 0)
				{
					if ((--m_remainingLoops) > 0)
					{
						rewind();
					}
				}
				else
				{
					rewind();
				}
			}
		}
	}

	return maxlen;
}

qint64 QAudioDecoderStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

void QAudioDecoderStream::rewind()
{
	m_output.seek(0);
}

void QAudioDecoderStream::bufferReady()
{
	const QAudioBuffer &buffer = m_decoder.read();

	const int length = buffer.byteCount();
	const char *data = buffer.data<char>();

	m_input.write(data, length);
}

void QAudioDecoderStream::finished()
{
	emit decodingFinished(this);
}

bool QAudioDecoderStream::atEnd() const
{
	return m_output.size()
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
	m_remainingLoops = m_loops;

	rewind();

	emit stateChanged(this, m_state);
}

QtMixer::State QAudioDecoderStream::state() const
{
	return m_state;
}

int QAudioDecoderStream::loops() const
{
	return m_loops;
}

void QAudioDecoderStream::setLoops(int loops)
{
	m_loops = loops;
	m_remainingLoops = loops;
}

int QAudioDecoderStream::position() const
{
	return m_output.pos()
		/ (m_format.sampleSize() / 8)
		/ (m_format.sampleRate() / 1000)
		/ (m_format.channelCount());
}

void QAudioDecoderStream::setPosition(int position)
{
	const int target = position
		* (m_format.sampleSize() / 8)
		* (m_format.sampleRate() / 1000)
		* (m_format.channelCount());

	m_output.seek(target);
}

int QAudioDecoderStream::length()
{
	return m_output.size()
		/ (m_format.sampleSize() / 8)
		/ (m_format.sampleRate() / 1000)
		/ (m_format.channelCount());
}
