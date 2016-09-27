#include <QtCore/QCoreApplication>

#include "testWeb.h"
int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	testWeb tw;
	
	return a.exec();
}
