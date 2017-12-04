#pragma once

#include <QDialog>
#include <QHeaderView>
#include <QMenu>
#include <QTreeWidget>

#include "DatabaseRef.h"
#include "EditCircleDialog.h"
#include "EditRectDialog.h"
#include "ObjectTreeItem.h"


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

	QTreeWidgetItem* mDummyRoot;	/*! Title root item. */
	QTreeWidgetItem* mGeometryRoot;	/*! The root for shapes. */
	QTreeWidgetItem* mSolverRoot;	/*! The root for the solver. */

	EditRectDialog* mRectDialog;	/*! The dialog for editing rectangles. */
	EditCircleDialog* mCircleDialog;/*! The dialog for editing circles. */

	const DatabaseRef databaseRef;	/*! Reference to the database. */
};
