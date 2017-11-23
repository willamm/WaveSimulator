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

void WaveSim::createRenderer()
{
	rc = make_unique<RenderController>(this, databaseRef);
}

void WaveSim::createObjectTree()
{
	objectTree = std::make_unique<ObjectTree>();
	connect(rc.get(), &RenderController::rectAdded, objectTree.get(), &ObjectTree::addItem);
	connect(rc.get(), &RenderController::circleAdded, objectTree.get(), &ObjectTree::addItem);
	connect(rc.get(), &RenderController::shapesCleared, objectTree.get(), &ObjectTree::clearShapes);
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

	connect(mAddRectDialog.get(), &AddRectDialog::RectSpecifiedSignal, rc.get(), &RenderController::AddRect);
	connect(mAddCircleDialog.get(), &AddCircleDialog::CircleSpecifiedSignal, rc.get(), &RenderController::AddCircle);
}

void WaveSim::createToolBarButtons()
{
	QToolBar* toolbar = ui.mainToolBar;
	createDialogs();

	QPushButton* startButton = new QPushButton("Start", this);
	QPushButton* stopButton = new QPushButton("Stop", this);
	QPushButton* singleStepButton = new QPushButton("Step Once", this);
	QPushButton* addRectButton = new QPushButton("Add Rect", this);
	QPushButton* addCircleButton = new QPushButton("Add Circle", this);
	QPushButton* resetFieldButton = new QPushButton("Reset Field", this);
	QPushButton* clearShapesButton = new QPushButton("Clear Shapes", this);

	connect(startButton, &QPushButton::pressed, rc.get(), &RenderController::startCalculation);
	connect(stopButton, &QPushButton::pressed, rc.get(), &RenderController::stopCalculation);
	connect(singleStepButton, &QPushButton::pressed, rc.get(), &RenderController::doOneTimestep);
	connect(addRectButton, &QPushButton::pressed, mAddRectDialog.get(), &QDialog::show);
	connect(addCircleButton, &QPushButton::pressed, mAddCircleDialog.get(), &QDialog::show);
	connect(resetFieldButton, &QPushButton::pressed, rc.get(), &RenderController::ResetField);
	connect(clearShapesButton, &QPushButton::pressed, rc.get(), &RenderController::ClearShapes);

	toolbar->addWidget(startButton);
	toolbar->addWidget(stopButton);
	toolbar->addWidget(singleStepButton);
	toolbar->addWidget(addRectButton);
	toolbar->addWidget(addCircleButton);
	toolbar->addWidget(resetFieldButton);
	toolbar->addWidget(clearShapesButton);
}

void WaveSim::connectMenuActions()
{
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	connect(ui.actionNew, &QAction::triggered, this, &WaveSim::New);
	connect(ui.actionOpen, &QAction::triggered, this, &WaveSim::Load);
	connect(ui.actionSave, &QAction::triggered, this, &WaveSim::Save);
}

void WaveSim::Save()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Choose Location to Save"), "./Saves", tr("JSON File (*.json)"));

	json saveJson = shapes->GetJson();

	ofstream outputFile;
	outputFile.open(fileName.toStdString());

	if (outputFile.is_open())
	{
		outputFile << saveJson;
	} //TODO: ADD FAILURE MESSAGE

	outputFile.close();

}

void WaveSim::Load()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Choose File to Open"), "./Saves", tr("JSON File (*.json)"));

	json loadJson;

	std::ifstream inputFile;
	inputFile.open(fileName.toStdString());

	if (inputFile.is_open())
	{
		inputFile >> loadJson;
	} //TODO: ADD FAILURE MESSAGE

	shapes->LoadJson(loadJson);
}

void WaveSim::New()
{
	rc->pauseCalculation();
	rc->ClearShapes();
	rc->ResetField();
}