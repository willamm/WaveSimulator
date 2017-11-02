#pragma once
#include <QMutex>
#include <QThread>
#include <QPainter>
#include <QPixmap>
#include <QVector>

#include "FieldArray.h"
#include "LCircle.h"
#include "LRect.h"
#include "LShape.h"
#include "WaveSolver.h"
#include "values.h"

class PaintThread
	: public QThread
{
	Q_OBJECT
public:
	
	PaintThread(WaveSolver<double>* solver, QVector<LShape<double>*>* shapes, QPixmap* pix, float fps, QObject* parent = nullptr);
	PaintThread(const PaintThread& pt);
	~PaintThread();

	class ThreadBuilder;

protected:
	void run();

private:
	bool mRunning;
	int mFPS;

	WaveSolver<double>* mSolver;
	QVector<LShape<double>*>* mShapes;

	QPixmap* mPix;
	std::unique_ptr<QPainter> mPainter;

	void paint();

signals:
	void paintDone();
};

class PaintThread::ThreadBuilder 
{
public:
private:

};