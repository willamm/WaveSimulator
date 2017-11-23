#pragma once
#include <QThread>
#include <QMutex>

#include "FieldArray.h"
#include "SettingsManager.h"
#include "WaveSolver.h"

class CalcThread : public QThread
{
	Q_OBJECT
public:
	CalcThread(WaveSolver<double>* solver, SettingsManager& settings, QObject* parent = nullptr);
	~CalcThread();

	void PerformOneTimestep();
	void SetDoCalculation(bool state);
	void SetRunning(bool state);
private:
	bool mRunning;
	bool mDoCalculation;
	QMutex mMutex;
	SettingsManager mSettings;
	WaveSolver<double>* mSolver;

protected:
	void run();

signals:
	void calculated();
};