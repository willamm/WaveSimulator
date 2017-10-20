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

// TODO: Make this class generic
class RenderController : public QWidget
{
	Q_OBJECT

public:
	RenderController(QWidget *parent);
	~RenderController();

	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);
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
