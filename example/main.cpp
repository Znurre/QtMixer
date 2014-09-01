#include <QApplication>
#include <QMixerStream>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QFile>

#include "MainWindow.h"

int main(int argc, char **argv)
{
	QApplication application(argc, argv);

	const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
	const QAudioFormat &format = device.preferredFormat();

	QMixerStream stream(format);
	QAudioOutput output(device, format);
	output.start(&stream);

	MainWindow window(stream);
	window.show();

	return application.exec();
}
