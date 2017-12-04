#pragma once

#include <fstream>
#include <iostream>
#include <memory>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QContextMenuEvent>
#include <QDesktopServices>
#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QStandardItemModel>
#include <QTreeView>
#include <QPushButton>
#include <QVBoxLayout>

#include "json.hpp"

#include "AddCircleDialog.h"
#include "AddRectDialog.h"
#include "ObjectTree.h"
#include "RenderController.h"
#include "ui_WaveSim.h"

using json = nlohmann::json;
using namespace std;

class WaveSim : public QMainWindow
{
	Q_OBJECT

public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim() = default;

private:
	Ui::WaveSimClass ui;							/*! The main Qt ui object. */
	unique_ptr<AddRectDialog> mAddRectDialog;		/*! The dialog window for entering a rectangle. */
	unique_ptr<AddCircleDialog> mAddCircleDialog;	/*! The dialog window for entering a cirle. */

	DatabaseRef databaseRef;						/*! A reference to a singleton flyweight object that contians all the data about the solver. */

	unique_ptr<RenderController> rc;				/*! The rendering viewport object. */
	unique_ptr<ObjectTree> objectTree;				/*! The object tree object. */

	void createToolBarButtons();
	void createRenderer();
	void createObjectTree();
	void createDialogs();
	void setLayout();
	void connectMenuActions();

public slots:
	void New();
	void Save();
	void Load();
	void sendToReadme();
	void sendToWiki();
};
