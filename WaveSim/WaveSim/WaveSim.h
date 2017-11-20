#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QVBoxLayout>
#include <QContextMenuEvent>
#include <QStandardItemModel>
#include <QObject>
#include <QPushButton>
#include <QTreeWidget>

#include "AddRectDialog.h"
#include "AddCircleDialog.h"
#include "ui_WaveSim.h"
#include "TreeItem.h"
#include "RenderController.h"

using namespace std;

class WaveSim : public QMainWindow
{
	Q_OBJECT

signals:
	void rectAdded(const int x, const int y, const int width, const int height);
	void circleAdded(const int x, const int y, const int radius);
	void shapesCleared();

public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim() = default;

public slots:
	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);
	void ClearShapes();
	void ResetField();

	void ShowContextMenu(const QPoint& event);

private:
	Ui::WaveSimClass ui;
	unique_ptr<AddRectDialog> mAddRectDialog;
	unique_ptr<AddCircleDialog> mAddCircleDialog;

	unique_ptr<RenderController> rc;
	shared_ptr<DatabaseRef> databaseRef;

	void createToolBarButtons();
	void createRenderer();
	void createObjectTree();
	void setLayout();
};
