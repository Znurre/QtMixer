#include <QDebug>
#include <QFile>

#include "SoundHandler.h"

SoundHandler::SoundHandler()
{
	QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
	QAudioFormat format;

	for (QAudioDeviceInfo device : devices)
	{
		if (device.deviceName() == "alsa_output.pci-0000_02_04.0.analog-stereo")
		{
			format = device.preferredFormat();
			format.setSampleSize(16);
			format.setSampleType(QAudioFormat::SignedInt);
			format.setSampleRate(44100);

			m_output = new QAudioOutput(device, format);
			m_output->setCategory("Foo");
		}

		qDebug() << device.deviceName();
	}

	m_stream.open(QIODevice::ReadOnly);
	m_stream.setFormat(format);

//	m_output->setBufferSize(16384);
	m_output->setVolume(0.5);
	m_output->start(&m_stream);
}

void SoundHandler::playSound(const QString &fileName)
{
	m_stream.openStream(fileName);
}
