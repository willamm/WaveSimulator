#include "WaveSim.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	WaveSim w;
	w.show();
	return app.exec();
}
