#include "MainWindow.h"

#include <QMixerStream>
#include <QHBoxLayout>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QMixerStream &mixer)
	: m_mixer(mixer)
{
	QWidget *centralWidget = new QWidget();
	QHBoxLayout *layout = new QHBoxLayout(centralWidget);

	m_sampleList = new QListWidget();
	m_streamList = new QListWidget();

	layout->addWidget(m_sampleList);
	layout->addWidget(m_streamList);

	setCentralWidget(centralWidget);

	m_sampleList->addItem("aztec.ogg");
	m_sampleList->addItem("squish.wav");
	m_sampleList->addItem("step0.wav");
	m_sampleList->addItem("switch.wav");

	connect(m_sampleList, &QListWidget::itemDoubleClicked, this, &MainWindow::sampleDoubleClicked);
	connect(m_streamList, &QListWidget::itemDoubleClicked, this, &MainWindow::streamDoubleClicked);
	connect(&m_mixer, &QMixerStream::stateChanged, this, &MainWindow::stateChanged);
}

void MainWindow::sampleDoubleClicked(QListWidgetItem *item)
{
	QString fileName = item->text();
	QFile *file = new QFile(fileName);

	if (file->open(QIODevice::ReadOnly))
	{
		QMixerStreamHandle handle = m_mixer.openRawStream(file);
		QListWidgetItem *item = new QListWidgetItem(fileName);

		m_streamListEntries << StreamListEntry(handle, item, file);
		m_streamList->addItem(item);

		handle.setLoops(10);
		handle.play();
	}
	else
	{
		delete file;
	}
}

void MainWindow::streamDoubleClicked(QListWidgetItem *item)
{
	for (const StreamListEntry &entry : m_streamListEntries)
	{
		if (entry.item() == item)
		{
			QMixerStreamHandle handle = entry.handle();
			handle.play();
		}
	}
}

void MainWindow::stateChanged(QMixerStreamHandle handle, QtMixer::State state)
{
	qDebug() << "state changed";

	for (const StreamListEntry &entry : m_streamListEntries)
	{
		if (entry.handle() == handle)
		{
			QListWidgetItem *item = entry.item();

			switch (state)
			{
				case QtMixer::Playing:
				{
					item->setIcon(QIcon::fromTheme("media-playback-start"));

					break;
				}

				case QtMixer::Paused:
				{
					item->setIcon(QIcon::fromTheme("media-playback-pause"));

					break;
				}

				case QtMixer::Stopped:
				{
					item->setIcon(QIcon::fromTheme("media-playback-stop"));

					break;
				}
			}
		}
	}
}
