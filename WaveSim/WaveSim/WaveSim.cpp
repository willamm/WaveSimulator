#include "WaveSim.h"

using namespace std;

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
	, databaseRef(DatabaseRef::GetInstance())
{
	ui.setupUi(this);

	createRenderer();
	createObjectTree();
	setLayout();
	createToolBarButtons();
	connectMenuActions();

	
}

WaveSim::~WaveSim()
{
}

void WaveSim::createRenderer()
{
	rc = std::make_unique<RenderController>(this, databaseRef);
}

void WaveSim::createObjectTree()
{
	objectTree = std::make_unique<ObjectTree>();
	connect(this, &WaveSim::rectAdded, objectTree.get(), &ObjectTree::addItem);
	connect(this, &WaveSim::circleAdded, objectTree.get(), &ObjectTree::addItem);
	connect(this, &WaveSim::shapesCleared, objectTree.get(), &ObjectTree::clearShapes);
}

void WaveSim::setLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);
	setMaximumHeight(rc->height());
	window->setMinimumHeight(rc->height());
	layout->addWidget(objectTree.get());
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

void WaveSim::connectMenuActions()
{
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	//connect(ui.actionNew, &QAction::triggered, this, DO SOMETHING);
	//connect(ui.actionOpen, &QAction::triggered, this, DO SOMETHING);
	//connect(ui.actionSave, &QAction::triggered, this, DO SOMETHING);
}

void WaveSim::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef.GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddRectangle(x, y, width, height, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddRect(x, y, width, height, vel);

	emit rectAdded(x, y, width, height);
}

void WaveSim::AddCircle(const int x, const int y, const int radius, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef.GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddCircle(x, y, radius, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddCircle(x, y, radius, vel);

	emit circleAdded(x, y, radius);
}

void WaveSim::ClearShapes()
{
	SolverModule* solver = (SolverModule*)databaseRef.GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetMaterials();

	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->ClearAllShapes();

	emit shapesCleared();
}

void WaveSim::ResetField()
{
	SolverModule* solver = (SolverModule*)databaseRef.GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetField();
}

