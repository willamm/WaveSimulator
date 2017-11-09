#include "RenderController.h"

RenderController::RenderController(QWidget *parent, std::shared_ptr<DatabaseRef> dbr)
	: QWidget(parent)
	, mShapes(std::dynamic_pointer_cast<ShapesModule>(dbr->GetModule(DatabaseRef::SHAPES_KEY)))
	, mSolver(std::make_shared<WaveSolver<double>>(X, Y))
	, mPix(std::make_unique<QPixmap>(X * PIXEL_SIZE, Y * PIXEL_SIZE))
	, mScene(std::make_unique<QGraphicsScene>(this))
	, mPixItem(mScene->addPixmap(*mPix))
	, mView(std::make_unique<QGraphicsView>(mScene.get(), this))
{
	mCThread = std::make_unique<CalcThread>(mSolver.get(), 1000 / FPS, this);
	mPThread = std::make_unique<PaintThread>(mSolver, dbr, mPix.get(), 1000 / FPS, this);

	connect(mPThread.get(), &PaintThread::paintDone, this, &RenderController::afterPainting);

	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mView->resize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);

	initThreads();
}

RenderController::~RenderController()
{
}

void RenderController::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	mSolver->addRectangle(x, y, x + width, y + height, vel);
	mShapes->AddRect(x, y, width, height, vel);
}

void RenderController::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolver->addCircle(x, y, radius, vel);
	mShapes->AddCircle(x, y, radius, vel);
}

void RenderController::ClearShapes()
{
	mSolver->resetMaterials();
	mShapes->ClearAllShapes();
}

void RenderController::ResetField()
{
	mSolver->resetField();
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
