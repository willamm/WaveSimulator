#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QVBoxLayout>

#include "ui_WaveSim.h"
#include "ObjectTreeModel.h"
#include "RenderController.h"

class WaveSim : public QMainWindow
{
	Q_OBJECT

signals:
	void rectAdded(const int x, const int y, const int width, const int height);
	void circleAdded(const int x, const int y, const int radius);
	void shapesCleared();

public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim();

	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);

public slots:
	void clicked(const QModelIndex& index);
	void ClearShapes();
	void ResetField();

private:
	Ui::WaveSimClass ui;
	std::unique_ptr<ObjectTreeModel> treeModel;
	std::unique_ptr<RenderController> rc;
	std::shared_ptr<DatabaseRef> databaseRef;

	void createToolBarButtons();
};
