QtMixer
=======

Summary
-----------

A lightweight software audio mixing library depending only on Qt.  
For use with QAudioOutput, using QAudioDecoder for decoding of input files.

Installation
-----------

Linux:

```
qmake
make
sudo make install
```

Windows (MSVC):

QtMixer can be compiled with MinGW too, but you won't get any sound.  
This is because QAudioDecoder relies on WMF on Windows (http://qt-project.org/wiki/Qt_Multimedia_Backends), which requires compiling with MSVC.

```
qmake
nmake
nmake install
```

Simple usage
-----------

```
QT += multimedia
CONFIG += mixer
```

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

QMixerStreamHandle handle1 = stream.openStream("music.ogg");
handle1.play();

QMixerStreamHandle handle2 = stream.openStream("sfx.wav");
handle2.setLoops(5);
handle2.play();
```
