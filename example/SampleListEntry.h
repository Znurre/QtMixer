#ifndef SAMPLELISTENTRY_H
#define SAMPLELISTENTRY_H

#include <QMixerStreamHandle>
#include <QListWidgetItem>

class StreamListEntry
{
	public:
		StreamListEntry(QMixerStreamHandle handle, QListWidgetItem *item, QIODevice *device);

		QMixerStreamHandle handle() const;
		QListWidgetItem *item() const;

		bool operator ==(const StreamListEntry &other) const;

	private:
		QMixerStreamHandle m_handle;

		QListWidgetItem *m_item;
		QIODevice *m_device;
};

#endif // SAMPLELISTENTRY_H
