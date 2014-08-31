#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>

#include "SoundHandler.h"

class Logic : public QObject
{
	public:
		Logic();

	private:
		void timerEvent(QTimerEvent *event) override;

		SoundHandler m_soundHandler;

		int m_ticks;
};

#endif // LOGIC_H
