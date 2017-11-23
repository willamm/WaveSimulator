#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QVector>
#include <QWidget>

#include "CalcThread.h"
#include "DatabaseRef.h"
#include "PaintThread.h"
#include "LCircle.h"
#include "LShape.h"
#include "LRect.h"
#include "SettingsManager.h"
#include "ShapesModule.h"
#include "SolverModule.h"

using namespace std;

// TODO: Make this class generic
class RenderController : public QWidget
{
	Q_OBJECT

public:
	RenderController(QWidget *parent, const DatabaseRef& dbr);
	~RenderController() = default;

private:
	SettingsManager mSettings;

	shared_ptr<ShapesModule> mShapes;
	shared_ptr<SolverModule> mSolver;

	unique_ptr<CalcThread> mCThread;
	unique_ptr<PaintThread> mPThread;

	unique_ptr<QPixmap> mPix;
	unique_ptr<QGraphicsScene> mScene;
	unique_ptr<QGraphicsPixmapItem> mPixItem;
	unique_ptr<QGraphicsView> mView;


private slots:
	void afterPainting();

public slots:
	void startCalculation();
	void doOneTimestep();
	void pauseCalculation();
	void stopCalculation();	
	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);
	void ClearShapes();
	void ResetField();

signals:
	void rectAdded(const int x, const int y, const int width, const int height);
	void circleAdded(const int x, const int y, const int radius);
	void shapesCleared();
};
