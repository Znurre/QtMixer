#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMixerStreamHandle>

#include "SampleListEntry.h"

class QMixerStream;

class MainWindow : public QMainWindow
{
	public:
		MainWindow(QMixerStream &mixer);

	private:
		void sampleDoubleClicked(QListWidgetItem *item);
		void streamDoubleClicked(QListWidgetItem *item);
		void stateChanged(QMixerStreamHandle handle, QtMixer::State state);

		QListWidget *m_sampleList;
		QListWidget *m_streamList;

		QMixerStream &m_mixer;

		QList<StreamListEntry> m_streamListEntries;
};

#endif // MAINWINDOW_H
