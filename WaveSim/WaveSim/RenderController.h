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
#include "values.h"

using namespace std;

// TODO: Make this class generic
class RenderController : public QWidget
{
	Q_OBJECT

public:
	RenderController(QWidget *parent, const DatabaseRef& dbr);
	~RenderController() = default;

private:
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
	void pauseCalculation();
	void stopCalculation();
};
