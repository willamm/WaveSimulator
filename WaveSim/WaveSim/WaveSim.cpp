#include "WaveSim.h"
#include "ObjectTreeModel.h"

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
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(treeView);
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
