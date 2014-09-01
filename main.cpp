#include <QCoreApplication>

#include <unistd.h>

#include "Logic.h"

int main(int argc, char **argv)
{
	QCoreApplication application(argc, argv);

	Logic logic;
	logic.startTimer(500);

	return application.exec();
}
