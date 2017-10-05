#include "WaveSim.h"
#include "ObjectTreeModel.h"

#include <QSplitter>
#include <QBoxLayout>
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

	test = new BBTest;
	test->setWindowFlags(Qt::Widget);

	QWidget* wrapper = new QWidget(this);
	QBoxLayout* vLayout = new QBoxLayout(QBoxLayout::LeftToRight, wrapper);
	vLayout->addWidget(treeView, 1, Qt::AlignLeft);
	vLayout->addWidget(test, 0, Qt::AlignRight);
	wrapper->setLayout(vLayout);
	setCentralWidget(wrapper);

	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}

WaveSim::~WaveSim()
{
	delete treeModel;
	delete treeView;
}
