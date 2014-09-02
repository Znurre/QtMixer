#ifndef QABSTRACTMIXERSTREAM_H
#define QABSTRACTMIXERSTREAM_H

#include <QIODevice>

#include "QtMixer.h"
#include "QMixerStreamHandle.h"

class QAbstractMixerStream : public QIODevice
{
	Q_OBJECT

	friend class QMixerStream;

	public:
		virtual void play() = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;

		virtual QtMixer::State state() const = 0;

		virtual int loops() const = 0;
		virtual void setLoops(int loops) = 0;

		virtual int position() const= 0;
		virtual void setPosition(int position) = 0;

		virtual int length() = 0;

	private:
		void removeFrom(QList<QAbstractMixerStream *> &streams)
		{
			streams.removeAll(this);
		}

	signals:
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);
		void decodingFinished(QMixerStreamHandle handle);
};

#endif // QABSTRACTMIXERSTREAM_H
