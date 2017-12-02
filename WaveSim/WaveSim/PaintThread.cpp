#include "PaintThread.h"

using namespace std;

/**
*	Contructor.
*
*	Creates a thread that handles painting pixels in Qt.
*
*	@param dbr A reference to the database.
*	@param pix The Qt pixmap to draw on.
*	@param settings The object containing settings about the viewport's meta data.
*	@param parent The parent Qt object.
*/
PaintThread::PaintThread(const DatabaseRef& dbr, QPixmap* pix, SettingsManager& settings, QObject* parent)
	: QThread(parent)
	, mRunning(true)
	, mSettings(settings)
	, mShapes(dynamic_pointer_cast<ShapesModule>(dbr.GetModule(DatabaseRef::SHAPES_KEY)))
	, mSolver(((SolverModule*)dbr.GetModule(DatabaseRef::SOLVER_KEY).get())->GetField())
	, mPix(pix)
	, mPainter(make_unique<QPainter>(pix))
{
}

/**
*	Deconstructor.
*
*	Sets the running variable to false to stop the thread.
*/
PaintThread::~PaintThread()
{
	mRunning = false;
	wait(1000);
}

/**
*	The main entry point for the thread.
*
*	Performs a paint operation once evert FPS / 1000 ms.
*/
void PaintThread::run()
{
	int frametime = 1000 / mSettings.GetValue(SettingsManager::KEY_FPS);
	QMutex mutex;
	while (mRunning)
	{
		mutex.lock();
		paint();
		mutex.unlock();

		emit paintDone();
		msleep(frametime);
	}
}


/**
*	The painting function.
*
*	Colors every cell a gray scale value from 0 - 255. 0 is mapped to 127 by default.
*	After drawing the thread, all shapes are drawn on top.
*/
void PaintThread::paint()
{
	int numOfX = mSolver->getField().numCellsX();
	int numOfY = mSolver->getField().numCellsY();
	int contrast = mSettings.GetValue(SettingsManager::KEY_COLOR_CONTRAST);
	int neutralColor = mSettings.GetValue(SettingsManager::KEY_NEUTRAL_COLOR);
	int pixelSize = mSettings.GetValue(SettingsManager::KEY_PIXEL_SIZE);

	for (int i = 0; i < numOfX; i++)
	{
		for (int j = 0; j < numOfY; j++)
		{
			double rgb = (mSolver->getField()(i, j) * 255 * contrast) + neutralColor;
			if (rgb > 255)
			{
				rgb = 255;
			}
			if (rgb < 0)
			{
				rgb = 0;
			}
			mPainter->fillRect(
				i * pixelSize, j * pixelSize
				, pixelSize, pixelSize
				, QColor(rgb, rgb, rgb)
			);
		}
	}

	for (auto& s : mShapes->GetShapes())
	{
		s->Draw(mPainter.get(), pixelSize);
	}
}
