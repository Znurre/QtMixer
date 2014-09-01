#include "Logic.h"

Logic::Logic()
	: m_ticks(0)
{
	m_soundHandler.playSound("aztec.ogg");
}

void Logic::timerEvent(QTimerEvent *event)
{
	if (m_ticks++ >= 4)
	{
		m_soundHandler.playSound("switch.wav");
		m_ticks = 0;
	}

	m_soundHandler.playSound("step0.wav");
}
