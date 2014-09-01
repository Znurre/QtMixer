#include "QMixerWrapperStream.h"
#include "QMixerStreamHandle.h"

QMixerWrapperStream::QMixerWrapperStream(QIODevice *device)
	: m_device(device)
	, m_state(QtMixer::Stopped)
	, m_loops(0)
	, m_remainingLoops(0)
{
	setOpenMode(QIODevice::ReadOnly);
}

bool QMixerWrapperStream::atEnd() const
{
	return m_device->atEnd();
}

void QMixerWrapperStream::play()
{
	m_state = QtMixer::Playing;

	emit stateChanged(this, m_state);
}

void QMixerWrapperStream::pause()
{
	m_state = QtMixer::Paused;

	emit stateChanged(this, m_state);
}

void QMixerWrapperStream::stop()
{
	m_state = QtMixer::Stopped;
	m_remainingLoops = m_loops;

	rewind();

	emit stateChanged(this, m_state);
}

QtMixer::State QMixerWrapperStream::state() const
{
	return m_state;
}

int QMixerWrapperStream::loops() const
{
	return m_loops;
}

void QMixerWrapperStream::setLoops(int loops)
{
	m_loops = loops;
	m_remainingLoops = loops;
}

qint64 QMixerWrapperStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	if (m_state == QtMixer::Playing)
	{
		m_device->read(data, maxlen);

		if (m_device->size() &&
			m_device->atEnd())
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

qint64 QMixerWrapperStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}

void QMixerWrapperStream::rewind()
{
	m_device->seek(0);
}
