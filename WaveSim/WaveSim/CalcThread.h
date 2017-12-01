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
	bool mRunning;	/*! The boolean that controls whether or not the thread is running. */
	bool mDoCalculation; /*! The boolean that controls whether or not the calculations are going. */
	QMutex mMutex;	/*! A mutex to prevent race conditions. */
	SettingsManager mSettings;	/*! The settings manager that handles misc values like FPS and size. */
	WaveSolver<double>* mSolver;	/*! The wave solver which is the main phyiscs engine. */

protected:
	void run();

signals:
	void calculated();
};