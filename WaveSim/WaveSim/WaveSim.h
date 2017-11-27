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
#include <QDesktopServices>
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
	void New();
	void Save();
	void Load();
	void sendToReadme();
	void sendToWiki();

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
};
