#ifndef DECODINGSTREAM_H
#define DECODINGSTREAM_H

#include <QIODevice>
#include <QBuffer>
#include <QAudioDecoder>
#include <QFile>

class DecodingStream : public QIODevice
{
	public:
		DecodingStream(const QString &fileName, const QAudioFormat &format);

		bool atEnd() const override;

	protected:
		qint64 readData(char *data, qint64 maxlen) override;
		qint64 writeData(const char *data, qint64 len) override;

	private:
		void bufferReady();

		QBuffer m_input;
		QBuffer m_output;
		QByteArray m_data;
		QAudioDecoder m_decoder;
		QFile m_file;

		bool m_atEnd;

};

#endif // DECODINGSTREAM_H
