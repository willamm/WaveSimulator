#include "WaveSim.h"
#include "ObjectTreeModel.h"

#include <QObject>

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

	QLayout* layout = new QHBoxLayout;
	layout->addWidget(treeView);

	test = new BBTest;
	test->setWindowFlags(Qt::Widget);
	layout->addWidget(test);

	QWidget* window = new QWidget;
	window->setLayout(layout);
	setCentralWidget(window);
	


	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}

WaveSim::~WaveSim()
{
	delete treeModel;
	delete treeView;
}
