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
