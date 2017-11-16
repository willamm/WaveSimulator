#include "CalcThread.h"

CalcThread::CalcThread(WaveSolver<double>* solver, const int fps, QObject* parent)
	: mSolver(solver)
	, mFPS(fps)
{
	mRunning = true;
	mDoCalculation = true;
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
		while (mDoCalculation)
		{
			mutex.lock();
			mSolver->doTimestep();
			mutex.unlock();
			emit calculated();
			msleep(mFPS);
		}
		msleep(mFPS);
	}
	
}

void CalcThread::setDoCalculation(bool state)
{
	mDoCalculation = state;
}

void CalcThread::setRunning(bool state)
{
	mRunning = state;
}
