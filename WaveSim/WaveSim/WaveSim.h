#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QVBoxLayout>

#include "ui_WaveSim.h"
#include "ObjectTreeModel.h"
#include "BBTest.h"

class WaveSim : public QMainWindow
{
	Q_OBJECT

public:
	WaveSim(QWidget *parent = Q_NULLPTR);
	~WaveSim();

private:
	Ui::WaveSimClass ui;
	QAbstractItemModel* treeModel;
	QTreeView* treeView;
	BBTest* test;
};
