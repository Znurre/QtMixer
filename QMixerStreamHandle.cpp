#include "QMixerStreamHandle.h"
#include "QAbstractMixerStream.h"

QMixerStreamHandle::QMixerStreamHandle()
	: m_stream(nullptr)
{

}

QMixerStreamHandle::QMixerStreamHandle(QAbstractMixerStream *stream)
	: m_stream(stream)
{

}

void QMixerStreamHandle::play()
{
	Q_ASSERT(m_stream);

	m_stream->play();
}

void QMixerStreamHandle::pause()
{
	Q_ASSERT(m_stream);

	m_stream->pause();
}

void QMixerStreamHandle::stop()
{
	Q_ASSERT(m_stream);

	m_stream->stop();
}

QtMixer::State QMixerStreamHandle::state() const
{
	Q_ASSERT(m_stream);

	return m_stream->state();
}

int QMixerStreamHandle::loops() const
{
	Q_ASSERT(m_stream);

	return m_stream->loops();
}

void QMixerStreamHandle::setLoops(int loops)
{
	Q_ASSERT(m_stream);

	m_stream->setLoops(loops);
}

int QMixerStreamHandle::position() const
{
	Q_ASSERT(m_stream);

	return m_stream->position();
}

void QMixerStreamHandle::setPosition(int position)
{
	Q_ASSERT(m_stream);

	m_stream->setPosition(position);
}

int QMixerStreamHandle::length() const
{
	Q_ASSERT(m_stream);

	return m_stream->length();
}

bool QMixerStreamHandle::operator ==(const QMixerStreamHandle &other) const
{
	return other.m_stream == m_stream;
}
