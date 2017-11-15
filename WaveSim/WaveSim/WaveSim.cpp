#include "WaveSim.h"

#include <QObject>
#include <QPushButton>

using namespace std;

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
	treeView->setMaximumHeight(rc->height());
	setMaximumHeight(rc->height());
	layout->addWidget(treeView);
	layout->addWidget(rc.get());
	window->setLayout(layout);
	setCentralWidget(window);
	
	connect(ui.actionExit, &QAction::triggered, this, &QMainWindow::close);

	AddRect(50, 50, 10, 10, 0);
}

void WaveSim::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddRectangle(x, y, width, height, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddRect(x, y, width, height, vel);
}

void WaveSim::AddCircle(const int x, const int y, const int radius, const double vel)
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->AddCircle(x, y, radius, vel);

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->AddCircle(x, y, radius, vel);
}

void WaveSim::ClearShapes()
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetMaterials();

	ShapesModule* shapes = (ShapesModule*)databaseRef->GetModule(DatabaseRef::SHAPES_KEY).get();
	shapes->ClearAllShapes();
}

void WaveSim::ResetField()
{
	SolverModule* solver = (SolverModule*)databaseRef->GetModule(DatabaseRef::SOLVER_KEY).get();
	solver->ResetField();
}

WaveSim::~WaveSim()
{
	delete treeModel;
	delete treeView;
}
