#include <QDebug>

#include "SoundHandler.h"

SoundHandler::SoundHandler()
	: m_output(QAudioDeviceInfo::defaultOutputDevice().preferredFormat())
{
	m_stream.open(QIODevice::ReadOnly);

	m_output.setVolume(1);
	m_output.start(&m_stream);

	qDebug() << m_output.periodSize() << m_output.bufferSize();
}

void SoundHandler::playSound(const QString &fileName)
{
	m_stream.openStream(fileName);
}
