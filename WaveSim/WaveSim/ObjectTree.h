#pragma once

#include <QDialog>
#include <QHeaderView>
#include <QMenu>
#include <QTreeWidget>

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

	inline EditRectDialog* GetEditRectDialog()
	{
		return mRectDialog;
	}

	inline EditCircleDialog* GetEditCircleDialog()
	{
		return mCircleDialog;
	}

public slots:
	void onContextMenuRequested(const QPoint& pos);
	void addItem();
	void clearShapes();

private:
	void showContextMenu(const ObjectTreeItem* item, const QPoint& pos) const;

	// Initialization

	QTreeWidgetItem* mDummyRoot;
	QTreeWidgetItem* mGeometryRoot;
	QTreeWidgetItem* mSolverRoot;

	EditRectDialog* mRectDialog;
	EditCircleDialog* mCircleDialog;

	const DatabaseRef databaseRef;
};
