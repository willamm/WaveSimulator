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
#include <QFileDialog>
#include <iostream>
#include <fstream>

#include "AddRectDialog.h"
#include "ObjectTree.h"
#include "AddCircleDialog.h"
#include "ui_WaveSim.h"
#include "RenderController.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class WaveSim : public QMainWindow
{
	Q_OBJECT
public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim() = default;

public slots:
	void AddRect(const int x, const int y, const int width, const int height, const double vel);
	void AddCircle(const int x, const int y, const int radius, const double vel);
	void ClearShapes();
	void ResetField();
	void New();
	void Save();
	void Load();

private:
	Ui::WaveSimClass ui;
	unique_ptr<AddRectDialog> mAddRectDialog;
	unique_ptr<AddCircleDialog> mAddCircleDialog;

	unique_ptr<RenderController> rc;
	DatabaseRef databaseRef;

	unique_ptr<ObjectTree> objectTree;

	void createToolBarButtons();
	void createRenderer();
	void createObjectTree();
	void createDialogs();
	void setLayout();
	void connectMenuActions();
	json getJsonFromStore();


signals:
	void rectAdded(const int x, const int y, const int width, const int height);
	void circleAdded(const int x, const int y, const int radius);
	void shapesCleared();
};
