#include "WaveSim.h"
#include <QObject>
#include <QPushButton>

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QObject::connect(ui.pushButton, SIGNAL (pressed()), this, SLOT(close()));
}
