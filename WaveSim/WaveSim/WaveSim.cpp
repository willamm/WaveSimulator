#include "WaveSim.h"
#include "ObjectTreeModel.h"

#include <QObject>
#include <QPushButton>

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::pressed, this, &WaveSim::close);
}
