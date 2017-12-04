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
	bool mRunning;						/*! The state of the main run thread. */

	SettingsManager mSettings;			/*! An object that handles all the misc settings like FPS and size. */
	WaveSolver<double>* mSolver;		/*! The wave solver that handles all the physics calculations. */
	shared_ptr<ShapesModule> mShapes;	/*! A reference to the shapes module. */
	QPixmap* mPix;						/*! The surface that is drawn on. */
	unique_ptr<QPainter> mPainter;		/*! The QPainting device that performs the drawing. */

	void paint();

signals:
	void paintDone();
};

class PaintThread::ThreadBuilder
{
public:
private:
};