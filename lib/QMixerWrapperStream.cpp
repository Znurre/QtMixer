#include "QMixerWrapperStream.h"
#include "QMixerStreamHandle.h"

QMixerWrapperStream::QMixerWrapperStream(QIODevice *device)
	: m_device(device)
	, m_state(QtMixer::Stopped)
{

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
	m_device->seek(0);

	emit stateChanged(this, m_state);
}

QtMixer::State QMixerWrapperStream::state() const
{
	return m_state;
}

qint64 QMixerWrapperStream::readData(char *data, qint64 maxlen)
{
	memset(data, 0, maxlen);

	if (m_state == QtMixer::Playing)
	{
		m_device->read(data, maxlen);
	}

	return maxlen;
}

qint64 QMixerWrapperStream::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data);
	Q_UNUSED(len);

	return 0;
}
