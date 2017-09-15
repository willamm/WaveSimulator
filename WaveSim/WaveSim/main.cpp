#include "WaveSim.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WaveSim w;
	w.show();
	return a.exec();
}
