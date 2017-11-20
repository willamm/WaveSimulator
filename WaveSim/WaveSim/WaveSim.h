#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QFile>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "AddRectDialog.h"
#include "AddCircleDialog.h"
#include "ui_WaveSim.h"
#include "ObjectTreeModel.h"
#include "LTreeView.h"
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
	void clicked(const QModelIndex& index);
	void ClearShapes();
	void ResetField();

private:
	Ui::WaveSimClass ui;
	unique_ptr<AddRectDialog> mAddRectDialog;
	unique_ptr<AddCircleDialog> mAddCircleDialog;

	unique_ptr<QTreeView> mTreeView;
	unique_ptr<RenderController> rc;
	shared_ptr<DatabaseRef> databaseRef;

	void createToolBarButtons();
	void createRenderer();
	void createObjectTree();
	void createDialogs();
	void setLayout();
};
