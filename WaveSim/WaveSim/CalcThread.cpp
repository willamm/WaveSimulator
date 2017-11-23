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

void CalcThread::PerformOneTimestep()
{
	QMutex mutex;
	mutex.lock();
	mSolver->doTimestep();
	mutex.unlock();
}

void CalcThread::SetDoCalculation(bool state)
{
	mDoCalculation = state;
}

void CalcThread::SetRunning(bool state)
{
	mRunning = state;
}
