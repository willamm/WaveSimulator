#include "CalcThread.h"

/**
*	Constructor.
*
*	Creates a thread that handles all phyics calculations.
*
*	@param solver The module that contians the solver.
*	@param settings	The object that contains settings about misc data like FPS an size.
*	@param parent The parent QObject.
*/
CalcThread::CalcThread(WaveSolver<double>* solver, SettingsManager& settings, QObject* parent)
	: mSolver(solver)
	, mSettings(settings)
{
	mRunning = true;
	mDoCalculation = true;
}

/**
*	Deconstructor
*
*	Sets running variable to false and waits for thread to stop.
*/
CalcThread::~CalcThread()
{
	mRunning = false;
	wait(1000);
}

/**
*	The main entry point of the thread.
*
*	Attempts to perform physics calculations in sync with the rendering.
*/
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

/**
*	Causes the WaveSolver to step forward one step in time.
*/
void CalcThread::PerformOneTimestep()
{
	mMutex.lock();
	mSolver->doTimestep();
	mMutex.unlock();
}

/**
*	Modifier method for the calculation boolean.
*	True for running, false to stop.
*
*	@param The new state.
*/
void CalcThread::SetDoCalculation(bool state)
{
	mDoCalculation = state;
}

/**
*	Modifier method for the running boolean.
*	True for running, false to stop.
*
*	@param The new state.
*/
void CalcThread::SetRunning(bool state)
{
	mRunning = state;
}
