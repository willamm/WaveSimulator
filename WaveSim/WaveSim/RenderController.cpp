#include "RenderController.h"

RenderController::RenderController(QWidget *parent)
	: QWidget(parent)
	, mSolver(new WaveSolver<double>(X, Y))
	, mShapes(new QVector<LShape<double>*>())
	, mPix(new QPixmap(X * PIXEL_SIZE, Y * PIXEL_SIZE))
	, mScene(new QGraphicsScene(this))
	, mPixItem(mScene->addPixmap(*mPix))
	, mView(new QGraphicsView(mScene, this))
{
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mView->resize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);
	initThreads();
}

RenderController::~RenderController()
{
	delete mCThread;
	delete mPThread;

	delete mSolver;
	delete mShapes;
	
	delete mView;
	delete mPixItem;
	delete mScene;
	delete mPix;
}

void RenderController::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	mSolver->addRectangle(x, y, x + width, y + height, vel);
	mShapes->append(new LRect<double>(x, y, width, height, vel));
}

void RenderController::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolver->addCircle(x, y, radius, vel);
	mShapes->append(new LCircle<double>(x, y, radius, vel));
}

void RenderController::ClearShapes()
{
	mSolver->resetMaterials();
	delete mShapes;
	mShapes = new QVector<LShape<double>*>();
}

void RenderController::ResetField()
{
	mSolver->resetField();
}

void RenderController::initThreads()
{
	mCThread = new CalcThread(mSolver, 1000 / FPS, this);
	mPThread = new PaintThread(mSolver, mShapes, mPix, 1000 / FPS, this);
	
	connect(mPThread, &PaintThread::paintDone, this, &RenderController::afterPainting);

	mCThread->start(QThread::HighPriority);
	mPThread->start(QThread::HighPriority);
}


void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}
