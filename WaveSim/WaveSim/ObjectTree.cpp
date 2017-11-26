#include "ObjectTree.h"

/**
* Constructor for ObjectTree.
* 
* @param parent The QWidget object that is the parent of this object.
*/
ObjectTree::ObjectTree(QWidget *parent)
	: QTreeWidget(parent)
	, dummyRoot(new QTreeWidgetItem(this))
	, databaseRef(DatabaseRef::GetInstance())
	, circleDialog(new EditCircleDialog(this))
	, rectDialog(new EditRectDialog(this))
{
	QStringList headerLabels;
	headerLabels << "Name" << "Type";
	setHeaderLabels(headerLabels);
	setColumnCount(2);
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setContextMenuPolicy(Qt::CustomContextMenu);

	addTopLevelItem(dummyRoot);
	dummyRoot->setText(0, "Root");
	dummyRoot->setText(1, "Root");
	dummyRoot->setExpanded(true);
	
	geometryRoot = new QTreeWidgetItem(dummyRoot);
	geometryRoot->setText(0, "Geometry");
	geometryRoot->setText(1, "Group");
	geometryRoot->setExpanded(true);

	solverRoot = new QTreeWidgetItem(dummyRoot);
	solverRoot->setText(0, "Solver");
	solverRoot->setText(1, "Group");
	solverRoot->setExpanded(true);

	connect(this, &ObjectTree::customContextMenuRequested, this, &ObjectTree::onContextMenuRequested);
}

ObjectTree::~ObjectTree()
{
	delete geometryRoot;
	delete dummyRoot;
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
	ObjectTreeItem* shapeNode = new ObjectTreeItem(geometryRoot, end);
	shapeNode->setText(0, QString::fromStdString(shapeNode->getShapeName()));
	shapeNode->setText(1, "Structure");
	geometryRoot->setExpanded(true);
}

void ObjectTree::clearShapes()
{
	geometryRoot->takeChildren();
}

void ObjectTree::showContextMenu(const ObjectTreeItem* item, const QPoint& pos) const
{
	QMenu menu;
	QString actionName = "Edit " + QString::fromStdString(item->getShapeName());
	QDialog* dialog;
	if (LCircle<double>* circle = dynamic_cast<LCircle<double>*>(item->getShape()))
	{
		
		circleDialog->setCircle(circle);
		dialog = circleDialog;
	}
	else if (LRect<double>* rect = dynamic_cast<LRect<double>*>(item->getShape()))
	{
		rectDialog->setRect(rect);
		dialog = rectDialog;
	}
	QAction* edit = menu.addAction(actionName, dialog, &QDialog::exec);
	menu.exec(pos);
}