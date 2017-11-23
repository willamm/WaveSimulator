#include "RenderController.h"

using namespace std;

RenderController::RenderController(QWidget *parent, const DatabaseRef& dbr)
	: QWidget(parent)
{
	mSettings.LoadSettingsFromFile();

	mShapes = dynamic_pointer_cast<ShapesModule>(dbr.GetModule(DatabaseRef::SHAPES_KEY));
	mSolver = dynamic_pointer_cast<SolverModule>(dbr.GetModule(DatabaseRef::SOLVER_KEY));

	const int x = mSettings.GetValue(SettingsManager::KEY_SIZE_X);
	const int y = mSettings.GetValue(SettingsManager::KEY_SIZE_Y);
	const int pixelSize = mSettings.GetValue(SettingsManager::KEY_PIXEL_SIZE);
	mPix = make_unique<QPixmap>(x * pixelSize, y * pixelSize);
	mScene = make_unique<QGraphicsScene>(this);
	mPixItem = make_unique<QGraphicsPixmapItem>(mScene->addPixmap(*mPix));
	mView = make_unique<QGraphicsView>(mScene.get(), this);

	mCThread = make_unique<CalcThread>(((SolverModule*)dbr.GetModule(DatabaseRef::SOLVER_KEY).get())->GetField(), mSettings, this);
	mPThread = make_unique<PaintThread>(dbr, mPix.get(), mSettings, this);

	connect(mPThread.get(), &PaintThread::paintDone, this, &RenderController::afterPainting);

	const int windowWidth = mSettings.GetValue(SettingsManager::KEY_WINDOW_WIDTH);
	const int windowHeight = mSettings.GetValue(SettingsManager::KEY_WINDOW_HEIGHT);

	setFixedSize(windowWidth, windowHeight);
	mView->resize(windowWidth + 2, windowHeight + 2);

	mPThread->start(QThread::HighPriority);

	mSettings.SaveSettingsToFile();
}

void RenderController::startCalculation()
{
	mCThread->SetDoCalculation(true);
	mCThread->SetRunning(true);
	mCThread->start(QThread::HighPriority);
}

void RenderController::doOneTimestep()
{
	mCThread->PerformOneTimestep();
}

void RenderController::pauseCalculation()
{
	mCThread->SetDoCalculation(false);
}

void RenderController::stopCalculation()
{
	mCThread->SetDoCalculation(false);
	mCThread->SetRunning(false);
	mCThread->exit();
}

void RenderController::AddRect(const int x, const int y, const int width, const int height, const double vel)
{
	mShapes->AddRect(x, y, width, height, vel);
	mSolver->AddRectangle(x, y, width, height, vel);
	emit rectAdded(x, y, width, height);
}

void RenderController::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mShapes->AddCircle(x, y, radius, vel);
	mSolver->AddCircle(x, y, radius, vel);
	emit circleAdded(x, y, radius);
}

void RenderController::ClearShapes()
{
	mShapes->ClearAllShapes();
	mSolver->ResetMaterials();
	emit shapesCleared();
}

void RenderController::ResetField()
{
	mSolver->ResetField();
}

void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}
