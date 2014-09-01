#ifndef QMIXERWRAPPERSTREAM_H
#define QMIXERWRAPPERSTREAM_H

#include "QAbstractMixerStream.h"

class QMixerWrapperStream : public QAbstractMixerStream
{
	public:
		QMixerWrapperStream(QIODevice *device);

		bool atEnd() const override;

		void play() override;
		void pause() override;
		void stop() override;

		QtMixer::State state() const override;

		int loops() const override;
		void setLoops(int loops) override;

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		void rewind();

		QIODevice *m_device;

		QtMixer::State m_state;

		int m_loops;
		int m_remainingLoops;
};

#endif // QMIXERWRAPPERSTREAM_H
