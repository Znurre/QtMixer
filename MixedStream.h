#ifndef MIXEDSTREAM_H
#define MIXEDSTREAM_H

#include <QIODevice>
#include <QList>

class MixedStream : public QIODevice
{
	const int CHANNELS = 16;

	public:
		MixedStream();

		void openStream(const QString &fileName);

		// QIODevice interface
	protected:
		qint64 readData(char *data, qint64 maxlen);
		qint64 writeData(const char *data, qint64 len);

	private:
		QList<QIODevice *> m_streams;
};

#endif // MIXEDSTREAM_H
