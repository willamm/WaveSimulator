#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QVector>
#include <QWidget>

#include "CalcThread.h"
#include "PaintThread.h"
#include "LCircle.h"
#include "LShape.h"
#include "LRect.h"
#include "WaveSolver.h"
#include "values.h"

// Make this class generic
class RenderController : public QWidget
{
	Q_OBJECT

public:
	RenderController(QWidget *parent);
	~RenderController();

	void AddRect(int x, int y, int width, int height, double vel);
	void AddCircle(int x, int y, int radius, double vel);
	void ClearShapes();
	void ResetField();

private:
	WaveSolver<double>* mSolver;

	CalcThread* mCThread;
	PaintThread* mPThread;

	QVector<LShape<double>*>* mShapes;

	QPixmap* mPix;
	QGraphicsScene* mScene;
	QGraphicsPixmapItem* mPixItem;
	QGraphicsView* mView;

	void initThreads();

private slots:
	void afterPainting();
};
