#include "RenderController.h"

using namespace std;

/**
* Constructor for the RenderController class.
*
* @param parent The parent object of the RenderController.
* @param dbr Reference to the database.
*/
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

/**
* Starts the calculation thread. Also makes the tool bar blue while 
* the calculation is going.
*/
void RenderController::startCalculation()
{
	qApp->setStyleSheet("QToolBar { background-color: #5fc3fc }");
	mCThread->SetDoCalculation(true);
	mCThread->SetRunning(true);
	mCThread->start(QThread::HighPriority);
}

/**
* Make the solver perform 1 timestep. 
*/
void RenderController::doOneTimestep()
{
	mCThread->PerformOneTimestep();
}

/**
* Pauses the calculation.
*/
void RenderController::pauseCalculation()
{
	mCThread->SetDoCalculation(false);
}

/**
* Stops the calculation thread, and changes the style of the tool bar.
*/
void RenderController::stopCalculation()
{
	qApp->setStyleSheet("");
	mCThread->SetDoCalculation(false);
	mCThread->SetRunning(false);
	mCThread->exit();
}

/**
* Adds a rectangle to the renderer.
*
* @param x The top left X-coordinate of the rectangle.
* @param y The top left Y-coordinate of the rectangle.
* @param w The width of the rectangle.
* @param h The height of the rectangle.
* @param vel The velocity of the rectangle. A higher velocity will make the
*			wave travel more slowly through the rectangle. A lower velocity
*			will do the opposite.
*/
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

/**
* Adds a circle the renderer.
* 
* @param x The X-coordinate of the center of the circle.
* @param y The Y-coordinate of the center of the circle.
* @param radius The radius of the circle.
* @param vel The velocity of the circle. Affects the behaviour of the wave when it
*			passes through the circle.
*/
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

/**
* Clears all of the shapes from the renderer.
*/
void RenderController::ClearShapes()
{
	mShapes->ClearAllShapes();
	mSolver->ResetMaterials();
	emit shapesCleared();
}

/**
* Resets the field. This causes the simulator to restart.
*/
void RenderController::ResetField()
{
	mSolver->ResetField();
}

/**
* Validates a rectangle before adding it to the renderer.
* 
* @param x The top left X-coordinate of the rectangle.
* @param y The top left Y-coordinate of the rectangle.
* @param w The width of the rectangle.
* @param h The height of the rectangle.
*
* @return True if the rectangle is valid, false otherwise.
*/
bool RenderController::validateRect(const int x, const int y, const int w, const int h)
{
	if (x < 1) return false;
	if (y < 1) return false;
	if (x + w > mSettings.GetValue(SettingsManager::KEY_SIZE_X)) return false;
	if (y + h > mSettings.GetValue(SettingsManager::KEY_SIZE_Y)) return false;
	return true;
}

/**
* Validates a circle before adding it to the renderer.
*
* @param x The X-coordinate of the center of the circle.
* @param y The Y-coordinate of the center of the circle.
* @param r The radius of the circle.
*
* @return True if the circle is valid, false otherwise.
*/
bool RenderController::validateCircle(const int x, const int y, const int r)
{
	if (x - r < 1) return false;
	if (y - r < 1) return false;
	if (x + r > mSettings.GetValue(SettingsManager::KEY_SIZE_X)) return false;
	if (y + r > mSettings.GetValue(SettingsManager::KEY_SIZE_Y)) return false;
	return true;
}

/**
*
*/
void RenderController::mousePressEvent(QMouseEvent * event)
{
	QPoint mouseLocation = QWidget::mapFromGlobal(QCursor::pos());
	int x = mouseLocation.x() / 3;
	int y = mouseLocation.y() / 3;

	if (event->button() == Qt::RightButton)
	{
		mSolver->setNewSource(x, y);
	}
	else if ((event->button() == Qt::LeftButton))
	{
		AddRect(x - 2, y - 2, 5, 5, 0);
	}

	
}

/**
* 
*/
void RenderController::afterPainting()
{
	mPixItem->setPixmap(*mPix);
	mView->show();
}

