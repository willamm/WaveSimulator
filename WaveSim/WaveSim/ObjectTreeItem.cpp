#include "ObjectTreeItem.h"
#include <QDebug>

ObjectTreeItem::ObjectTreeItem(QTreeWidgetItem* parent, LShape<double>* shape)
	: QTreeWidgetItem(parent)
	, m_shape(shape)
{
}

/**
* When called, returns what type of shape it is.
*
* @return The type of shape
*/
const std::string ObjectTreeItem::getShapeName() const
{
	return m_shape->GetClassName();
}


/**
* Returns the shape in the object tree
*
* @return The shape.
*/
LShape<double>* ObjectTreeItem::getShape() const
{
	return m_shape;
}
