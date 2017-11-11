#include "RenderController.h"

using namespace std;

RenderController::RenderController(QWidget *parent, std::shared_ptr<DatabaseRef> dbr)
	: QWidget(parent)
	, mShapesModule(dynamic_pointer_cast<ShapesModule>(dbr->GetModule(DatabaseRef::SHAPES_KEY)))
	, mSolverModule(dynamic_pointer_cast<SolverModule>(dbr->GetModule(DatabaseRef::SOLVER_KEY)))
	, mPix(std::make_unique<QPixmap>(X * PIXEL_SIZE, Y * PIXEL_SIZE))
	, mScene(std::make_unique<QGraphicsScene>(this))
	, mPixItem(mScene->addPixmap(*mPix))
	, mView(std::make_unique<QGraphicsView>(mScene.get(), this))
{
	mCThread = make_unique<CalcThread>(mSolverModule->GetField(), 1000 / FPS, this);
	mPThread = make_unique<PaintThread>(mSolverModule->GetField(), dbr, mPix.get(), 1000 / FPS, this);

	connect(mPThread.get(), &PaintThread::paintDone, this, &RenderController::afterPainting);

	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mView->resize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);

	initThreads();
}

void RenderController::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	mSolverModule->AddRectangle(x, y, width, height, vel);
	mShapesModule->AddRect(x, y, width, height, vel);
}

void RenderController::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolverModule->AddCircle(x, y, radius, vel);
	mShapesModule->AddCircle(x, y, radius, vel);
}

void RenderController::ClearShapes()
{
	mSolverModule->ResetMaterials();
	mShapesModule->ClearAllShapes();
}

void RenderController::ResetField()
{
	mSolverModule->ResetField();
}

void RenderController::initThreads()
{
	mCThread->start(QThread::HighPriority);
	mPThread->start(QThread::HighPriority);
}


void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}
