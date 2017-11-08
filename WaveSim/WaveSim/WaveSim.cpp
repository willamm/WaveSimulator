#include "WaveSim.h"

#include <QObject>
#include <QPushButton>

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QFile file(":/default.txt");
	file.open(QIODevice::ReadOnly);
	treeModel = new ObjectTreeModel(file.readAll());
	file.close();

	treeView = new QTreeView;
	treeView->setModel(treeModel);
	rc = new RenderController(this);

	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);

	treeView->setMaximumHeight(rc->height());
	setMaximumHeight(rc->height());

	layout->addWidget(treeView);
	layout->addWidget(rc);
	
	window->setLayout(layout);

	setCentralWidget(window);
	
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}

WaveSim::~WaveSim()
{
	delete treeModel;
	delete treeView;
	delete rc;
}
