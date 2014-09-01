#include <QCoreApplication>
#include <QMixerStream>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QFile>

int main(int argc, char **argv)
{
	QCoreApplication application(argc, argv);

	const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
	const QAudioFormat &format = device.preferredFormat();

	QMixerStream stream(format);
	QAudioOutput output(device, format);
	output.start(&stream);
	output.setVolume(0.5);

	QFile file("aztec.ogg");

	if (file.open(QIODevice::ReadOnly))
	{
		QMixerStreamHandle handle = stream.openEncodedStream(&file);

		Q_UNUSED(handle);
	}

	return application.exec();
}
