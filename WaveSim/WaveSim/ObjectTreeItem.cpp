#include "ObjectTreeItem.h"
#include <QDebug>

ObjectTreeItem::ObjectTreeItem(QTreeWidgetItem* parent, LShape<double>* shape)
	: QTreeWidgetItem(parent)
	, m_shape(shape)
{
}

const std::string ObjectTreeItem::getShapeName() const
{
	return m_shape->GetClassName();
}

LShape<double>* ObjectTreeItem::getShape() const
{
	return m_shape;
}
