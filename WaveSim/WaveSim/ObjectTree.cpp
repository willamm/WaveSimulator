#include "ObjectTree.h"

/**
*	Constructor for ObjectTree.
* 
*	@param parent The QWidget object that is the parent of this object.
*/
ObjectTree::ObjectTree(QWidget *parent)
	: QTreeWidget(parent)
	, mDummyRoot(new QTreeWidgetItem(this))
	, databaseRef(DatabaseRef::GetInstance())
	, mCircleDialog(new EditCircleDialog(this))
	, mRectDialog(new EditRectDialog(this))
{
	QStringList headerLabels;
	headerLabels << "Name" << "Type";
	setHeaderLabels(headerLabels);
	setColumnCount(2);
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setContextMenuPolicy(Qt::CustomContextMenu);

	addTopLevelItem(mDummyRoot);
	mDummyRoot->setText(0, "Root");
	mDummyRoot->setText(1, "Root");
	mDummyRoot->setExpanded(true);
	
	mGeometryRoot = new QTreeWidgetItem(mDummyRoot);
	mGeometryRoot->setText(0, "Geometry");
	mGeometryRoot->setText(1, "Group");
	mGeometryRoot->setExpanded(true);

	mSolverRoot = new QTreeWidgetItem(mDummyRoot);
	mSolverRoot->setText(0, "Solver");
	mSolverRoot->setText(1, "Group");
	mSolverRoot->setExpanded(true);

	connect(this, &ObjectTree::customContextMenuRequested, this, &ObjectTree::onContextMenuRequested);
}

ObjectTree::~ObjectTree()
{
	delete mGeometryRoot;
	delete mDummyRoot;
	// throws exception
	//delete solverRoot;
}

void ObjectTree::onContextMenuRequested(const QPoint& pos)
{
	ObjectTreeItem* item = dynamic_cast<ObjectTreeItem*>(itemAt(pos));
	if (item)
	{
		showContextMenu(item, viewport()->mapToGlobal(pos));
	}
}

void ObjectTree::addItem()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	LShape<double>* end = shapes->GetShapes().back().get();
	ObjectTreeItem* shapeNode = new ObjectTreeItem(mGeometryRoot, end);
	shapeNode->setText(0, QString::fromStdString(shapeNode->getShapeName()));
	shapeNode->setText(1, "Structure");
	mGeometryRoot->setExpanded(true);
}

void ObjectTree::clearShapes()
{
	mGeometryRoot->takeChildren();
}

void ObjectTree::showContextMenu(const ObjectTreeItem* item, const QPoint& pos) const
{
	QMenu menu;
	QString actionName = "Edit " + QString::fromStdString(item->getShapeName());
	QDialog* dialog;

	if (LCircle<double>* circle = dynamic_cast<LCircle<double>*>(item->getShape()))
	{
		mCircleDialog->setCircle(circle);
		dialog = mCircleDialog;
	}
	else if (LRect<double>* rect = dynamic_cast<LRect<double>*>(item->getShape()))
	{
		mRectDialog->setRect(rect);
		dialog = mRectDialog;
	}

	QAction* edit = menu.addAction(actionName, dialog, &QDialog::show);
	menu.exec(pos);
}