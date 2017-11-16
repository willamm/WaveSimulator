#include "WaveSim.h"

#include <QObject>
#include <QPushButton>
#include <QStandardItemModel>

using namespace std;

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
	, databaseRef(std::make_shared<DatabaseRef>())
{
	ui.setupUi(this);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();

	// Shapes added here so that they show in the object model
	AddRect(50, 50, 10, 10, 0);
	AddCircle(100, 75, 30, 0);

	int numRows = shapes->GetShapes().size();
	QStandardItemModel* standardTreeModel = new QStandardItemModel(this);
	QList<QStandardItem*> columns;
	QStandardItem* rootItem = standardTreeModel->invisibleRootItem();
	standardTreeModel->setHorizontalHeaderLabels(QStringList() << "Name" << "Type");
	QStandardItem* root = new QStandardItem("Root");
	QStandardItem* geometryItem = new QStandardItem("Geometry");
	QList<QStandardItem*> geoRow;
	geoRow << geometryItem << new QStandardItem("Group");
	columns << root << new QStandardItem("Root");
	rootItem->appendRow(columns);
	root->appendRow(geoRow);
	standardTreeModel->appendRow(columns);
	for (int row = 0; row < numRows; row++)
	{
		QList<QStandardItem*> shapesRow;
		QStandardItem* item = new QStandardItem(QString(shapes->GetShapes()[row]->GetClassName().c_str()));
		shapesRow << item << new QStandardItem(QString("Structure"));
		geometryItem->appendRow(shapesRow);
	}
	root->appendRow(new QStandardItem("Solver"));

	rc = std::make_unique<RenderController>(this, databaseRef);

	QTreeView* treeView = new QTreeView(this);
	treeView->setModel(standardTreeModel);
	
	// Emit event when an item in the view is clicked
	connect(treeView, &QTreeView::clicked, this, &WaveSim::clicked);

	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);
	treeView->setMaximumHeight(rc->height());
	setMaximumHeight(rc->height());
	layout->addWidget(treeView);
	layout->addWidget(rc.get());
	window->setLayout(layout);
	setCentralWidget(window);

	createToolBarButtons();
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	
	// Add connection for AddRect, AddCircle, ClearShapes
}

void WaveSim::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddRectangle(x, y, width, height, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddRect(x, y, width, height, vel);

	emit rectAdded(x, y, width, height);
}

void WaveSim::AddCircle(const int x, const int y, const int radius, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddCircle(x, y, radius, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddCircle(x, y, radius, vel);

	emit circleAdded(x, y, radius);
}

void WaveSim::ClearShapes()
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetMaterials();

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->ClearAllShapes();

	emit shapesCleared();
}

void WaveSim::ResetField()
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetField();

	// Might have to emit something here
}

void WaveSim::createToolBarButtons()
{
	QToolBar* toolbar = ui.mainToolBar;

	QPushButton* startButton = new QPushButton("Start", this);
	QPushButton* stopButton = new QPushButton("Stop", this);
	QPushButton* addRectButton = new QPushButton("Add Rect", this);
	QPushButton* addCircleButton = new QPushButton("Add Circle", this);
	QPushButton* resetFieldButton = new QPushButton("Reset Field", this);
	QPushButton* clearShapesButton = new QPushButton("Clear Shapes", this);

	connect(startButton, &QPushButton::pressed, rc.get(), &RenderController::startCalculation);
	connect(stopButton, &QPushButton::pressed, rc.get(), &RenderController::stopCalculation);

	connect(resetFieldButton, &QPushButton::pressed, this, &WaveSim::ResetField);
	connect(clearShapesButton, &QPushButton::pressed, this, &WaveSim::ClearShapes);

	toolbar->addWidget(startButton);
	toolbar->addWidget(stopButton);
	toolbar->addWidget(addRectButton);
	toolbar->addWidget(addCircleButton);
	toolbar->addWidget(resetFieldButton);
	toolbar->addWidget(clearShapesButton);
}

void WaveSim::clicked(const QModelIndex& index)
{

}

WaveSim::~WaveSim()
{
}
