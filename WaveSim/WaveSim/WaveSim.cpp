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

WaveSim::~WaveSim()
{
	delete geometryRoot;
}

void WaveSim::createRenderer()
{
	rc = std::make_unique<RenderController>(this, databaseRef);
}

void WaveSim::createObjectTree()
{
	QTreeWidgetItem* dummyRoot = ui.treeWidget->topLevelItem(0);
	dummyRoot->setText(0, "Root");
	dummyRoot->setText(1, "Root");

	geometryRoot = dummyRoot->child(0);
	geometryRoot->setText(0, "Geometry");
	geometryRoot->setText(1, "Group");

	connect(this, &WaveSim::rectAdded, &WaveSim::AddItemToObjectTree);
	connect(this, &WaveSim::circleAdded, &WaveSim::AddItemToObjectTree);
}

void WaveSim::setLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);
	setMaximumHeight(rc->height());
	ui.treeWidget->setMaximumHeight(rc->height());
	window->setMinimumHeight(rc->height());
	layout->addWidget(ui.treeWidget);
	layout->addWidget(rc.get());
	window->setLayout(layout);
	setCentralWidget(window);
}

void WaveSim::createToolBarButtons()
{
	mAddRectDialog = make_unique<AddRectDialog>(this);
	mAddCircleDialog = make_unique<AddCircleDialog>(this);

	QToolBar* toolbar = ui.mainToolBar;

	QPushButton* startButton = new QPushButton("Start", this);
	QPushButton* stopButton = new QPushButton("Stop", this);
	QPushButton* addRectButton = new QPushButton("Add Rect", this);
	QPushButton* addCircleButton = new QPushButton("Add Circle", this);
	QPushButton* resetFieldButton = new QPushButton("Reset Field", this);
	QPushButton* clearShapesButton = new QPushButton("Clear Shapes", this);

	connect(startButton, &QPushButton::pressed, rc.get(), &RenderController::startCalculation);
	connect(stopButton, &QPushButton::pressed, rc.get(), &RenderController::stopCalculation);

	connect(addRectButton, &QPushButton::pressed, mAddRectDialog.get(), &QDialog::show);
	connect(mAddRectDialog.get(), &AddRectDialog::RectSpecifiedSignal, this, &WaveSim::AddRect);

	connect(addCircleButton, &QPushButton::pressed, mAddCircleDialog.get(), &QDialog::show);
	connect(mAddCircleDialog.get(), &AddCircleDialog::CircleSpecifiedSignal, this, &WaveSim::AddCircle);

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

void WaveSim::ShowContextMenu(const QPoint& point)
{
}

void WaveSim::AddItemToObjectTree()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	QTreeWidgetItem* shapeNode = new QTreeWidgetItem;
	const auto& end = shapes->GetShapes().back().get();
	QString shapeName = QString::fromStdString(end->GetClassName());
	shapeNode->setText(0, shapeName);
	shapeNode->setText(1, "Structure");
	geometryRoot->addChild(shapeNode);
	geometryRoot->setExpanded(true);
	geometryRoot->treeWidget()->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
