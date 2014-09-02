QtMixer
=======

Summary
-----------

A lightweight software audio mixing library depending only on Qt.  
For use with QAudioOutput, using QAudioDecoder for decoding of input files.

Installation
-----------

Build and copy lib files to /usr/local/lib  
Copy the following header files to /usr/local/include/QtMixer:  

QMixerStream.h  
QMixerStream  
QMixerStreamHandle.h  
QMixerStreamHandle  
QtMixer.h  

Simple usage
-----------

```C++
#include <QMixerStream>
#include <QMixerStreamHandle>
```

```C++
const QAudioDeviceInfo &device = QAudioDeviceInfo::defaultOutputDevice();
const QAudioFormat &audioFormat = device.preferredFormat();

QMixerStream stream(audioFormat);
QAudioOutput output(device, audioFormat);
output.setVolume(0.5);
output.start(&stream);

QFile musicFile("music.ogg");
QFile soundFile("sfx.wav");

if (musicFile.open(QIODevice::ReadOnly))
{
	QMixerStreamHandle handle = stream.openStream(&musicFile);
	handle.play();
}

if (soundFile.open(QIODevice::ReadOnly))
{
	QMixerStreamHandle handle = stream.openStream(&soundFile);
	handle.setLoops(5);
	handle.play();
}
```
