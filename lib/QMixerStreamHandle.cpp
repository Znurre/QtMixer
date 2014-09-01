#include "QMixerStreamHandle.h"
#include "QAbstractMixerStream.h"

QMixerStreamHandle::QMixerStreamHandle(QAbstractMixerStream *stream)
	: m_stream(stream)
{

}

void QMixerStreamHandle::play()
{
	m_stream->play();
}

void QMixerStreamHandle::pause()
{
	m_stream->pause();
}

void QMixerStreamHandle::stop()
{
	m_stream->stop();
}

QtMixer::State QMixerStreamHandle::state() const
{
	return m_stream->state();
}

int QMixerStreamHandle::loops() const
{
	return m_stream->loops();
}

void QMixerStreamHandle::setLoops(int loops)
{
	m_stream->setLoops(loops);
}

bool QMixerStreamHandle::operator ==(const QMixerStreamHandle &other) const
{
	return other.m_stream == m_stream;
}
