#ifndef QMIXERWRAPPERSTREAM_H
#define QMIXERWRAPPERSTREAM_H

#include "QAbstractMixerStream.h"

class QMixerWrapperStream : public QAbstractMixerStream
{
	public:
		QMixerWrapperStream(QIODevice *device);

		void play() override;
		void pause() override;
		void stop() override;

		QtMixer::State state() const override;

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		QIODevice *m_device;

		QtMixer::State m_state;
};

#endif // QMIXERWRAPPERSTREAM_H
