#include "PaintThread.h"
#include <QDebug> 

PaintThread::PaintThread(std::shared_ptr<WaveSolver<double>> solver, std::shared_ptr<DatabaseRef> dbr, QPixmap* pix, float fps, QObject* parent)
	: QThread(parent)
	, mRunning(true)
	, mFPS(fps)
	, mShapes(std::dynamic_pointer_cast<ShapesModule>(dbr->GetModule(DatabaseRef::SHAPES_KEY)))
	, mSolver(solver)
	, mPix(pix)
	, mPainter(std::make_unique<QPainter>(pix))
{
}

PaintThread::PaintThread(const PaintThread& pt)
{
}

PaintThread::~PaintThread()
{
	mRunning = false;
	wait(1000);
}

void PaintThread::run()
{
	QMutex mutex;
	while (mRunning)
	{
		mutex.lock();
		paint();
		mutex.unlock();

		emit paintDone();
		msleep(mFPS);
	}
}

void PaintThread::paint()
{
	double rgb;
	int numOfX = mSolver->getField().numCellsX();
	int numOfY = mSolver->getField().numCellsY();

	for (int i = 0; i < numOfX; i++)
	{
		for (int j = 0; j < numOfY; j++)
		{
			rgb = (mSolver->getField()(i, j) * 255 * COLOR_CONSTRAST) + MIDDLE_COLOR;
			if (rgb > 255)
			{
				rgb = 255;
			}
			if (rgb < 0)
			{
				rgb = 0;
			}
			mPainter->fillRect(
				i * PIXEL_SIZE, j * PIXEL_SIZE
				, PIXEL_SIZE, PIXEL_SIZE
				, QColor(rgb, rgb, rgb)
			);
			// Exception Thrown here when closing program? Access violation executing location 0x0000000200000000
		}
	}

	// This is not running even though the loop about is
	std::vector<std::unique_ptr<LShape<double>>> vec = mShapes->GetShapes();
	for (int k = 0; k < vec.size(); k++)
	{
		vec.at(k)->Draw(mPainter.get());
	}
}
