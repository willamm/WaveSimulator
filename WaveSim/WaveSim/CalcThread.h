#pragma once
#include <QThread>
#include <QMutex>

#include "FieldArray.h"
#include "WaveSolver.h"

class CalcThread
	: public QThread
{
	Q_OBJECT
public:
	CalcThread(WaveSolver<double>* solver, const int mFPS, QObject* parent = nullptr);
	~CalcThread();

	void PerformOneTimestep();
	void SetDoCalculation(bool state);
	void SetRunning(bool state);
private:
	bool mRunning;
	bool mDoCalculation;
	const int mFPS;
	WaveSolver<double>* mSolver;

protected:
	void run();

signals:
	void calculated();
};