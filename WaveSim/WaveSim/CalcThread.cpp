#include "CalcThread.h"

CalcThread::CalcThread(WaveSolver<double>* solver, SettingsManager& settings, QObject* parent)
	: mSolver(solver)
	, mSettings(settings)
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
	int frametime = 1000 / mSettings.GetValue(SettingsManager::KEY_FPS);
	while (mRunning) 
	{
		while (mDoCalculation)
		{
			mMutex.lock();
			mSolver->doTimestep();
			mMutex.unlock();
			emit calculated();
			msleep(frametime);
		}
		msleep(frametime);
	}
	
}

void CalcThread::PerformOneTimestep()
{
	mMutex.lock();
	mSolver->doTimestep();
	mMutex.unlock();
}

void CalcThread::SetDoCalculation(bool state)
{
	mDoCalculation = state;
}

void CalcThread::SetRunning(bool state)
{
	mRunning = state;
}
