#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMessageBox>
#include <QVector>
#include <QWidget>
#include <QMouseEvent>

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

class RenderController : public QWidget
{
	Q_OBJECT

public:
	RenderController(QWidget *parent, const DatabaseRef& dbr);
	~RenderController() = default;

private:
	SettingsManager mSettings;	/*! Manages settings specific to meta data about the solver like size and fps. */

	shared_ptr<ShapesModule> mShapes; /*! A reference to the shapes module. */
	shared_ptr<SolverModule> mSolver; /*! A reference to the solver module. */

	unique_ptr<CalcThread> mCThread; /*! A thread that handles all WaveSolver calcuations. */
	unique_ptr<PaintThread> mPThread; /*! A thread that handles all the GUI calculations. */

	unique_ptr<QPixmap> mPix;
	unique_ptr<QGraphicsScene> mScene;
	unique_ptr<QGraphicsPixmapItem> mPixItem;
	unique_ptr<QGraphicsView> mView;

	bool isValidRect(const int x, const int y, const int w, const int h);
	bool isValidCircle(const int x, const int y, const int r);
	void mousePressEvent(QMouseEvent *event) override;

private slots:
	void afterPainting();

public slots:
	void startCalculation();
	void doOneTimestep();
	void pauseCalculation();
	void stopCalculation();
	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);
	void EditRect(LRect<double>* rect, const int x, const int y, const int widht, const int height, const double vel);
	void EditCircle(LCircle<double>* circle, const int x, const int y, const int radius, const double vel);
	void ClearShapes();
	void ResetField();

signals:
	void rectAdded(const int x, const int y, const int width, const int height);
	void circleAdded(const int x, const int y, const int radius);
	void shapesCleared();
};
