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
	if (validateRect(x, y, width, height))
	{
		mShapes->AddRect(x, y, width, height, vel);
		mSolver->AddRectangle(x, y, width, height, vel);
		emit rectAdded(x, y, width, height);
	}
	else
	{
		QMessageBox::warning(this, "Out of Bounds", "The rectangle you are trying to add exceeds the allowed boundaries");
	}
}

void RenderController::AddCircle(const int x, const int y, const int radius, const double vel)
{
	if (validateCircle(x, y, radius))
	{
		mShapes->AddCircle(x, y, radius, vel);
		mSolver->AddCircle(x, y, radius, vel);
		emit circleAdded(x, y, radius);
	}
	else
	{
		QMessageBox::warning(this, "Out of Bounds", "The circle you are trying to add exceeds the allowed boundaries");
	}
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

bool RenderController::validateRect(const int x, const int y, const int w, const int h)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x + w > mSettings.GetValue(SettingsManager::KEY_SIZE_X)) return false;
	if (y + h > mSettings.GetValue(SettingsManager::KEY_SIZE_Y)) return false;
	return true;
}

bool RenderController::validateCircle(const int x, const int y, const int r)
{
	if (x - r < 0) return false;
	if (y - r < 0) return false;
	if (x + r > mSettings.GetValue(SettingsManager::KEY_SIZE_X)) return false;
	if (y + r > mSettings.GetValue(SettingsManager::KEY_SIZE_Y)) return false;
	return true;
}

void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}

