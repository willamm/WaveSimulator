#pragma once

#include <QTreeWidget>
#include <QHeaderView>
#include <QDialog>
#include <QMenu>
// for debugging
#include <QDebug>

#include "DatabaseRef.h"
#include "ObjectTreeItem.h"
#include "EditCircleDialog.h"
#include "EditRectDialog.h"


class ObjectTree : public QTreeWidget
{
	Q_OBJECT

public:
	ObjectTree(QWidget* parent = 0);
	~ObjectTree();

signals:
	void shapeEdited();

public slots:
	void onContextMenuRequested(const QPoint& pos);
	void addItem();
	void clearShapes();

private:
	void showContextMenu(const ObjectTreeItem* item, const QPoint& pos) const;

	// Initialization

	QTreeWidgetItem* dummyRoot;
	QTreeWidgetItem* geometryRoot;
	QTreeWidgetItem* solverRoot;

	EditRectDialog* rectDialog;
	EditCircleDialog* circleDialog;

	const DatabaseRef databaseRef;
};
