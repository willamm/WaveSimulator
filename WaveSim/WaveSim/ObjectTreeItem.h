#pragma once

#include <QTreeWidgetItem>
#include <memory>

#include "LShape.h"

class ObjectTreeItem : public QTreeWidgetItem
{
public:
	ObjectTreeItem(QTreeWidgetItem* parent, LShape<double>* shape);
	virtual ~ObjectTreeItem() = default;

	const std::string getShapeName() const;
	LShape<double>* getShape() const;

private:
	LShape<double>* m_shape;
};
