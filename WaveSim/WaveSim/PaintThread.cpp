#include "PaintThread.h"
#include <QDebug> 

PaintThread::PaintThread(WaveSolver<double>* solver, QVector<LShape<double>*>* shapes, QPixmap* pix, float fps, QObject* parent)
	: QThread(parent)
	, mRunning(true)
	, mFPS(fps)
	, mSolver(solver)
	, mShapes(shapes)
	, mPix(pix)
	, mPainter(new QPainter(pix))
{
}

PaintThread::~PaintThread()
{
	mRunning = false;
	wait();
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
		}
	}

	for (int k = 0; k < mShapes->size(); k++)
	{
		mShapes->at(k)->Draw(mPainter);
	}
}
