#pragma once

#include <QTreeWidget>
#include <QHeaderView>
#include <QMenu>

#include "DatabaseRef.h"

class ObjectTree : public QTreeWidget
{
	Q_OBJECT

public:
	ObjectTree(QWidget* parent = 0);
	~ObjectTree();

public slots:
	void onContextMenuRequested(const QPoint& pos);
	void addItem();
	void clearShapes();

private:
	void showContextMenu(const QTreeWidgetItem* item, const QPoint& pos) const;

	// Initialization

	QTreeWidgetItem* dummyRoot;
	QTreeWidgetItem* geometryRoot;
	QTreeWidgetItem* solverRoot;

	const DatabaseRef databaseRef;
};
