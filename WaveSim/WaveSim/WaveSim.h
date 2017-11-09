#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QVBoxLayout>

#include "ui_WaveSim.h"
#include "DatabaseRef.h"
#include "ObjectTreeModel.h"
#include "RenderController.h"

class WaveSim : public QMainWindow
{
	Q_OBJECT

public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim();

private:
	Ui::WaveSimClass ui;
	ObjectTreeModel* treeModel;
	QTreeView* treeView;
	std::unique_ptr<RenderController> rc;
	std::shared_ptr<DatabaseRef> databaseRef;
};
