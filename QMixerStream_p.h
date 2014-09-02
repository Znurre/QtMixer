#ifndef QMIXERSTREAM_P_H
#define QMIXERSTREAM_P_H

#include <QList>
#include <QAudioFormat>

class QMixerStream;
class QAbstractMixerStream;

class QMixerStreamPrivate
{
	friend class QMixerStream;

	public:
		QMixerStreamPrivate(const QAudioFormat &format);

	private:
		QList<QAbstractMixerStream *> m_streams;
		QAudioFormat m_format;
};

#endif // QMIXERSTREAM_P_H
