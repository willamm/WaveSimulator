#include "RenderController.h"

using namespace std;

RenderController::RenderController(QWidget *parent, std::shared_ptr<DatabaseRef> dbr)
	: QWidget(parent)
	, mPix(std::make_unique<QPixmap>(X * PIXEL_SIZE, Y * PIXEL_SIZE))
	, mScene(std::make_unique<QGraphicsScene>(this))
	, mPixItem(mScene->addPixmap(*mPix))
	, mView(std::make_unique<QGraphicsView>(mScene.get(), this))
{
	mCThread = make_unique<CalcThread>(((SolverModule*)dbr->GetModule(DatabaseRef::SOLVER_KEY).get())->GetField(), 1000 / FPS, this);
	mPThread = make_unique<PaintThread>(dbr, mPix.get(), 1000 / FPS, this);

	connect(mPThread.get(), &PaintThread::paintDone, this, &RenderController::afterPainting);

	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	mView->resize(WINDOW_WIDTH + 2, WINDOW_HEIGHT + 2);

	mPThread->start(QThread::HighPriority);
}

void RenderController::startCalculation()
{
	mCThread->setDoCalculation(true);
	mCThread->setRunning(true);
	mCThread->start(QThread::HighPriority);
}

void RenderController::pauseCalculation()
{
	mCThread->setDoCalculation(false);
}

void RenderController::stopCalculation()
{
	mCThread->setDoCalculation(false);
	mCThread->setRunning(false);
	mCThread->exit();
}

void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}
