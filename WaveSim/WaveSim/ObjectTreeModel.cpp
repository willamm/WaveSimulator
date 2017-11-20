#include "ObjectTreeModel.h"

ObjectTreeModel::ObjectTreeModel(QObject* parent)
	: QAbstractItemModel(parent)
{
	std::vector<std::string> columnHeaders;
	columnHeaders.push_back("Root");
	columnHeaders.push_back("Root");
	m_rootItem = std::make_shared<TreeRow>(columnHeaders);

	std::shared_ptr<TreeRow> child = std::make_shared<TreeRow>(columnHeaders);
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex & index) const
{
	return Qt::DisplayRole | Qt::ToolTipRole;
}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal) 
	{
		switch (role)
		{
			case Qt::DisplayRole:
				return QString::fromStdString(m_rootItem->getRowStrings()[section]);
		}
		
	}
	return QVariant();
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex & parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}
	TreeRow* rowItem = m_rootItem.get();
	if (parent.isValid())
	{
		rowItem = static_cast<TreeRow*>(parent.internalPointer());
	}
	std::shared_ptr<TreeRow> childItem = rowItem->getChild(row);
	if (childItem)
	{
		return createIndex(row, column, (void*)childItem.get());
	}
	return QModelIndex();
}

QModelIndex ObjectTreeModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}
	TreeRow* rowItem = static_cast<TreeRow*>(index.internalPointer());
	TreeRow* parent = rowItem->getParentItem().get();
	// Parent is the root
	if (parent == m_rootItem.get())
	{
		return QModelIndex();
	}
	return createIndex(parent->row(), 0, (void*)parent);
}

int ObjectTreeModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
	{
		return m_rootItem->childCount();
	}
	if (parent.column() > 0)
	{
		return 0;
	}
	TreeRow* item = static_cast<TreeRow*>(parent.internalPointer());
	return item->childCount();
}

int ObjectTreeModel::columnCount(const QModelIndex& parent) const
{
	return 0;
}

QVariant ObjectTreeModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	TreeRow* rowItem = static_cast<TreeRow*>(index.internalPointer());
	if (rowItem)
	{
		switch (role)
		{
			case Qt::DisplayRole:
			{
				return QString::fromStdString(rowItem->getRowStrings()[0]);
			}
		}
	}
	return QVariant();
}

const std::shared_ptr<TreeRow>& ObjectTreeModel::getRoot() const
{
	return m_rootItem;
}

void ObjectTreeModel::addRow(const QModelIndex & index, const std::shared_ptr<TreeRow> child)
{
	if (!index.isValid()) 
	{
		return;
	}
	TreeRow* rowItem = static_cast<TreeRow*>(index.internalPointer());
	if (!rowItem)
	{
		return;
	}
	beginInsertRows(index, rowItem->childCount(), rowItem->childCount());
	rowItem->appendChild(child);
	endInsertRows();
}

void ObjectTreeModel::setupModelDataFromDB(const std::shared_ptr<DatabaseRef>& dbRef)
{

}

void ObjectTreeModel::addShapeToTree()
{

}
