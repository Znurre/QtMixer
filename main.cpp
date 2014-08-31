#include <QCoreApplication>

#include "Logic.h"

int main(int argc, char **argv)
{
	QCoreApplication application(argc, argv);

	Logic logic;
	logic.startTimer(200);

	return application.exec();
}
