#include "SampleListEntry.h"

StreamListEntry::StreamListEntry(QMixerStreamHandle handle, QListWidgetItem *item, QIODevice *device)
	: m_handle(handle)
	, m_item(item)
	, m_device(device)
{

}

QMixerStreamHandle StreamListEntry::handle() const
{
	return m_handle;
}

QListWidgetItem *StreamListEntry::item() const
{
	return m_item;
}

bool StreamListEntry::operator ==(const StreamListEntry &other) const
{
	return other.m_handle == m_handle;
}
