#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <QString>
#include <QAudioOutput>

#include "MixedStream.h"

class SoundHandler
{
	public:
		SoundHandler();

		void playSound(const QString &fileName);

	private:
		QAudioOutput m_output;

		MixedStream m_stream;
};

#endif // SOUNDHANDLER_H
