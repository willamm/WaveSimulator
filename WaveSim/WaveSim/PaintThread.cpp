#include "PaintThread.h"
#include <QDebug> 

using namespace std;

PaintThread::PaintThread(std::shared_ptr<DatabaseRef> dbr, QPixmap* pix, const int fps, QObject* parent)
	: QThread(parent)
	, mRunning(true)
	, mFPS(fps)
	, mShapes(dynamic_pointer_cast<ShapesModule>(dbr->GetModule(DatabaseRef::SHAPES_KEY)))
	, mSolver(((SolverModule*)dbr->GetModule(DatabaseRef::SOLVER_KEY).get())->GetField())
	, mPix(pix)
	, mPainter(make_unique<QPainter>(pix))
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

	for (auto& s : mShapes->GetShapes())
	{
		s->Draw(mPainter.get());
	}
}
