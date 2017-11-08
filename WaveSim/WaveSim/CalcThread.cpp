#include "CalcThread.h"

CalcThread::CalcThread(WaveSolver<double>* solver, const int fps, QObject* parent)
	: mSolver(solver)
	, mFPS(fps)
{
	mRunning = true;
}

CalcThread::~CalcThread()
{
	mRunning = false;
	wait(1000);
}

void CalcThread::run()
{
	QMutex mutex;
	while (mRunning)
	{
		mutex.lock();
		mSolver->doTimestep();
		mutex.unlock();
		emit calculated();
		msleep(mFPS);
	}
}