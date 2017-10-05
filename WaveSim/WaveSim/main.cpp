#include "ObjectTreeModel.h"
#include "WaveSim.h"



int main(int argc, char *argv[])
{
	//Q_INIT_RESOURCE(simpletreemodel);
	QApplication app(argc, argv);
	WaveSim w;
	w.show();
	return app.exec();
}
