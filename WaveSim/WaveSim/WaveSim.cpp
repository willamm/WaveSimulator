#include "WaveSim.h"

using namespace std;

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
	, databaseRef(std::make_shared<DatabaseRef>())
{
	ui.setupUi(this);

	createRenderer();
	createObjectTree();
	setLayout();
	createToolBarButtons();

	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
}

void WaveSim::createRenderer()
{
	rc = std::make_unique<RenderController>(this, databaseRef);
}

void WaveSim::createObjectTree()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
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

	mTreeView = make_unique<LTreeView>(this);
	mTreeView->setModel(standardTreeModel);
	
	// Emit event when an item in the view is clicked
	connect(mTreeView.get(), &QTreeView::clicked, this, &WaveSim::clicked);
}

void WaveSim::setLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);
	mTreeView->setMaximumHeight(rc->height());
	setMaximumHeight(rc->height());
	layout->addWidget(mTreeView.get());
	layout->addWidget(rc.get());
	window->setLayout(layout);
	setCentralWidget(window);
}

void WaveSim::createDialogs()
{
	mAddRectDialog = make_unique<AddRectDialog>(this);
	mAddCircleDialog = make_unique<AddCircleDialog>(this);

	mAddRectDialog->setWindowTitle("Add Rectangle");
	mAddCircleDialog->setWindowTitle("Add Circle");

	connect(mAddRectDialog.get(), &AddRectDialog::RectSpecifiedSignal, this, &WaveSim::AddRect);
	connect(mAddCircleDialog.get(), &AddCircleDialog::CircleSpecifiedSignal, this, &WaveSim::AddCircle);
}

void WaveSim::createToolBarButtons()
{
	QToolBar* toolbar = ui.mainToolBar;
	createDialogs();

	QPushButton* startButton = new QPushButton("Start", this);
	QPushButton* stopButton = new QPushButton("Stop", this);
	QPushButton* addRectButton = new QPushButton("Add Rect", this);
	QPushButton* addCircleButton = new QPushButton("Add Circle", this);
	QPushButton* resetFieldButton = new QPushButton("Reset Field", this);
	QPushButton* clearShapesButton = new QPushButton("Clear Shapes", this);

	connect(startButton, &QPushButton::pressed, rc.get(), &RenderController::startCalculation);
	connect(stopButton, &QPushButton::pressed, rc.get(), &RenderController::stopCalculation);
	connect(addRectButton, &QPushButton::pressed, mAddRectDialog.get(), &QDialog::show);
	connect(addCircleButton, &QPushButton::pressed, mAddCircleDialog.get(), &QDialog::show);
	connect(resetFieldButton, &QPushButton::pressed, this, &WaveSim::ResetField);
	connect(clearShapesButton, &QPushButton::pressed, this, &WaveSim::ClearShapes);

	toolbar->addWidget(startButton);
	toolbar->addWidget(stopButton);
	toolbar->addWidget(addRectButton);
	toolbar->addWidget(addCircleButton);
	toolbar->addWidget(resetFieldButton);
	toolbar->addWidget(clearShapesButton);
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
}

void WaveSim::clicked(const QModelIndex& index)
{
	
}