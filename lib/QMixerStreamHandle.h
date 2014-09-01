#ifndef QMIXERSTREAMHANDLE_H
#define QMIXERSTREAMHANDLE_H

#include "QtMixer.h"

class QAbstractMixerStream;
class QAudioDecoderStream;
class QMixerWrapperStream;
class QMixerStream;

class QTMIXER_EXPORT QMixerStreamHandle
{
	friend class QMixerStream;
	friend class QAudioDecoderStream;
	friend class QMixerWrapperStream;

	public:
		void play();
		void pause();
		void stop();

		QtMixer::State state() const;

		int loops() const;
		void setLoops(int loops);

		bool operator ==(const QMixerStreamHandle &other) const;

	private:
		QMixerStreamHandle(QAbstractMixerStream *stream);

		QAbstractMixerStream *m_stream;
};

#endif // QMIXERSTREAMHANDLE_H