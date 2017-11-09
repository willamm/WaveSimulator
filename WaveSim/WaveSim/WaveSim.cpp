#include "WaveSim.h"

#include <QObject>
#include <QPushButton>

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
	, databaseRef(std::make_shared<DatabaseRef>())
{
	ui.setupUi(this);

	QFile file(":/default.txt");
	file.open(QIODevice::ReadOnly);
	treeModel = new ObjectTreeModel(file.readAll());
	file.close();

	treeView = new QTreeView;
	treeView->setModel(treeModel);
	rc = std::make_unique<RenderController>(this, databaseRef);

	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);

	layout->addWidget(treeView);
	layout->addWidget(rc.get());
	
	window->setLayout(layout);

	setCentralWidget(window);
	
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);

	rc->AddRect(50, 50, 10, 10, 0);
}

WaveSim::~WaveSim()
{
	delete treeModel;
	delete treeView;
}
