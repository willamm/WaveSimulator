#pragma once
#include <memory>

#include <QMutex>
#include <QThread>
#include <QPainter>
#include <QPixmap>
#include <QVector>

#include "DatabaseRef.h"
#include "FieldArray.h"
#include "LCircle.h"
#include "LRect.h"
#include "LShape.h"
#include "SettingsManager.h"
#include "ShapesModule.h"
#include "WaveSolver.h"

using namespace std;

class PaintThread : public QThread
{
	Q_OBJECT
public:
	
	PaintThread(const DatabaseRef& dbr, QPixmap* pix, SettingsManager& settings, QObject* parent = nullptr);
	PaintThread(const PaintThread& pt);
	~PaintThread();

	class ThreadBuilder;

protected:
	void run();

private:
	bool mRunning;

	SettingsManager mSettings;
	WaveSolver<double>* mSolver;
	shared_ptr<ShapesModule> mShapes;
	QPixmap* mPix;
	unique_ptr<QPainter> mPainter;

	void paint();

signals:
	void paintDone();
};

class PaintThread::ThreadBuilder 
{
public:
private:

};