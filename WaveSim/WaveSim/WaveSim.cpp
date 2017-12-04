#include "WaveSim.h"

using namespace std;

/**
*	Constructor for the main parent window of the program.
*	
*	@param parent The parent QWidget.
*/
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

/**
*	Creates the viewport for the renderer.
*/
void WaveSim::createRenderer()
{
	rc = make_unique<RenderController>(this, databaseRef);
}

/**
*	Creates the object tree component.
*/
void WaveSim::createObjectTree()
{
	objectTree = make_unique<ObjectTree>();
	connect(rc.get(), &RenderController::rectAdded, objectTree.get(), &ObjectTree::addItem);
	connect(rc.get(), &RenderController::circleAdded, objectTree.get(), &ObjectTree::addItem);
	connect(rc.get(), &RenderController::shapesCleared, objectTree.get(), &ObjectTree::clearShapes);
	connect(objectTree->GetEditRectDialog(), &EditRectDialog::RectEdited, rc.get(), &RenderController::EditRect);
	connect(objectTree->GetEditCircleDialog(), &EditCircleDialog::CircleEdited, rc.get(), &RenderController::EditCircle);
}

/**
*	Sets up the layout for the entire window.
*/
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

/**
*	Creates the dialog boxes.
*
*	Instantiates the AddRect and AddCircle dialog boxes so they can be shown when needed.
*/
void WaveSim::createDialogs()
{
	mAddRectDialog = make_unique<AddRectDialog>(this);
	mAddCircleDialog = make_unique<AddCircleDialog>(this);

	mAddRectDialog->setWindowTitle("Add Rectangle");
	mAddCircleDialog->setWindowTitle("Add Circle");

	connect(mAddRectDialog.get(), &AddRectDialog::RectSpecifiedSignal, rc.get(), &RenderController::AddRect);
	connect(mAddCircleDialog.get(), &AddCircleDialog::CircleSpecifiedSignal, rc.get(), &RenderController::AddCircle);
}

/**
*	Creates the buttons for the toolbar.
*
*	The buttons are created in this order:
*	[Start][Stop][Step][Add Rect][Add Circle][Reset Field][Clear Shapes]
*/
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

/**
*	Sets up the connections for the menu actions.
*/
void WaveSim::connectMenuActions()
{
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);
	connect(ui.actionNew, &QAction::triggered, this, &WaveSim::New);
	connect(ui.actionOpen, &QAction::triggered, this, &WaveSim::Load);
	connect(ui.actionSave, &QAction::triggered, this, &WaveSim::Save);
	connect(ui.actionAbout_Wave_Simulator, &QAction::triggered, this, &WaveSim::sendToReadme);
	connect(ui.actionWiki, &QAction::triggered, this, &WaveSim::sendToWiki);
}

/**
*	Saves the current set of shapes to a json file.
*/
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
	}

	outputFile.close();

}

/**
*	Loads a json file and populates the shapes from the json file.
*/
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
		try
		{
			inputFile >> loadJson;

			//If JSON is successfully deserialized, pause and clear the solver so we have a blank canvas to add shapes to
			rc->pauseCalculation();
			rc->ClearShapes();
			rc->ResetField();
		}
		catch (std::invalid_argument)
		{
			QMessageBox::warning(this, "Invalid JSON", "The file you are trying to load is invalid");
		}

		inputFile.close();
	}

	for (json::iterator it = loadJson.begin(); it != loadJson.end(); ++it) {
		json temp = *it;

		if (temp["Classname"] == "Circle")
		{
			rc->AddCircle(temp["X"], temp["Y"], temp["Radius"], temp["Velocity"]);
		}
		else if (temp["Classname"] == "Rectangle")
		{
			rc->AddRect(temp["X"], temp["Y"], temp["Width"], temp["Height"], temp["Velocity"]);
		}
	}

}

/**
*	Resets the state of the program to the default state.
*/
void WaveSim::New()
{
	rc->pauseCalculation();
	rc->ClearShapes();
	rc->ResetField();
}

/**
*	Links the user to the readme file.
*/
void WaveSim::sendToReadme()
{
	QDesktopServices::openUrl(QUrl("https://github.com/willamm/WaveSimulator#wavesimulator", QUrl::TolerantMode));
}

/**
*	Links the user to the wiki page.
*/
void WaveSim::sendToWiki()
{
	QDesktopServices::openUrl(QUrl("https://github.com/willamm/WaveSimulator/wiki", QUrl::TolerantMode));
}