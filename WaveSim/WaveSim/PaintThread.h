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

class PaintThread : public QThread
{
	Q_OBJECT
public:
	PaintThread(WaveSolver<double>* solver, QVector<LShape<double>*>* shapes, QPixmap* pix, const float fps, QObject* parent = nullptr);
	~PaintThread();

protected:
	void run();

private:
	bool mRunning;
	const int mFPS;

	WaveSolver<double>* mSolver;
	QVector<LShape<double>*>* mShapes;

	QPixmap* mPix;
	QPainter* mPainter;

	void paint();

signals:
	void paintDone();
};