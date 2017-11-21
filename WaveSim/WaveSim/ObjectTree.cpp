#include "ObjectTree.h"

const static int ShapeType = QTreeWidgetItem::UserType + 1;

ObjectTree::ObjectTree(QWidget *parent)
	: QTreeWidget(parent)
	, dummyRoot(new QTreeWidgetItem(this))
	, databaseRef(DatabaseRef::GetInstance())
{
	QStringList headerLabels;
	headerLabels << "Name" << "Type";
	setHeaderLabels(headerLabels);
	setColumnCount(2);
	setContextMenuPolicy(Qt::CustomContextMenu);
	header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	addTopLevelItem(dummyRoot);
	dummyRoot->setText(0, "Root");
	dummyRoot->setText(1, "Root");
	
	geometryRoot = new QTreeWidgetItem(dummyRoot);
	geometryRoot->setText(0, "Geometry");
	geometryRoot->setText(1, "Group");

	solverRoot = new QTreeWidgetItem(dummyRoot);
	solverRoot->setText(0, "Solver");
	solverRoot->setText(1, "Group");

	connect(this, &ObjectTree::customContextMenuRequested, this, &ObjectTree::onContextMenuRequested);
}

ObjectTree::~ObjectTree()
{
}

void ObjectTree::onContextMenuRequested(const QPoint& pos)
{
	QTreeWidgetItem* item = itemAt(pos);
	if (item)
	{
		showContextMenu(item, viewport()->mapToGlobal(pos));
	}
}

void ObjectTree::addItem()
{
	ShapesModule* shapes = (ShapesModule*)databaseRef.GetModule(DatabaseRef::SHAPES_KEY).get();
	QTreeWidgetItem* shapeNode = new QTreeWidgetItem(geometryRoot);
	const auto& end = shapes->GetShapes().back().get();
	QString shapeName = QString::fromStdString(end->GetClassName());
	shapeNode->setText(0, shapeName);
	shapeNode->setText(1, "Structure");
	geometryRoot->setExpanded(true);
}

void ObjectTree::clearShapes()
{
	geometryRoot->takeChildren();
}

void ObjectTree::showContextMenu(const QTreeWidgetItem* item, const QPoint& pos) const
{
	QMenu menu;
	menu.addAction("Edit");
	
	switch (item->type())
	{
	case ShapeType:
		menu.exec(pos);
	}
}