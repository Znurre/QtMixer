#ifndef QAUDIODECODERSTREAM_H
#define QAUDIODECODERSTREAM_H

#include <QBuffer>
#include <QAudioDecoder>

#include "QAbstractMixerStream.h"

class QAudioDecoderStream : public QAbstractMixerStream
{
	public:
		QAudioDecoderStream(QIODevice *device, const QAudioFormat &format);

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
		void bufferReady();

		QBuffer m_input;
		QBuffer m_output;
		QByteArray m_data;
		QAudioDecoder m_decoder;

		QtMixer::State m_state;

		int m_loops;
		int m_remainingLoops;
};

#endif // QAUDIODECODERSTREAM_H
