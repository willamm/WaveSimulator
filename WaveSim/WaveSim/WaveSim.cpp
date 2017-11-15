#include "WaveSim.h"

#include <QObject>
#include <QPushButton>

using namespace std;

WaveSim::WaveSim(QWidget *parent)
	: QMainWindow(parent)
	, databaseRef(std::make_shared<DatabaseRef>())
{
	ui.setupUi(this);

	treeModel = std::make_unique<ObjectTreeModel>(*databaseRef);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();

	treeView.setModel(treeModel.get());

	rc = std::make_unique<RenderController>(this, databaseRef);

	QHBoxLayout* layout = new QHBoxLayout(this);
	QWidget* window = new QWidget(this);
	treeView.setMaximumHeight(rc->height());
	setMaximumHeight(rc->height());
	layout->addWidget(&treeView);
	layout->addWidget(rc.get());
	window->setLayout(layout);
	setCentralWidget(window);

	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);

	AddRect(50, 50, 10, 10, 0);

	// Add connection for AddRect, AddCircle, ClearShapes

}

void WaveSim::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddRectangle(x, y, width, height, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddRect(x, y, width, height, vel);

	emit rectAdded(x, y, width, height); // Add shape data?
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

WaveSim::~WaveSim()
{
}
