#include "PaintThread.h"
#include <QDebug> 

PaintThread::PaintThread(WaveSolver<double>* solver, QVector<LShape<double>*>* shapes, QPixmap* pix, float fps, QObject* parent)
	: QThread(parent)
	, mRunning(true)
	, mFPS(fps)
	, mSolver(solver)
	, mShapes(shapes)
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
		}
	}

	for (const auto& shapes : *mShapes)
	{
		shapes->Draw(mPainter.get());
	}
}
