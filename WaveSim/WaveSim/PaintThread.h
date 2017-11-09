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
#include "ShapesModule.h"
#include "WaveSolver.h"
#include "values.h"

class PaintThread
	: public QThread
{
	Q_OBJECT
public:
	
	PaintThread(std::shared_ptr<WaveSolver<double>> solver, std::shared_ptr<DatabaseRef> dbr, QPixmap* pix, const int fps, QObject* parent = nullptr);
	PaintThread(const PaintThread& pt);
	~PaintThread();

	class ThreadBuilder;

protected:
	void run();

private:
	bool mRunning;
	int mFPS;

	std::shared_ptr<WaveSolver<double>> mSolver;
	std::shared_ptr<ShapesModule> mShapes;

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