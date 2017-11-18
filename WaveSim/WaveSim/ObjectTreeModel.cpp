#include "ObjectTreeModel.h"

ObjectTreeModel::ObjectTreeModel(const std::shared_ptr<DatabaseRef>& dbRef, QObject* parent)
	: QAbstractItemModel(parent)
{
	setupModelDataFromDB(dbRef);
}

ObjectTreeModel::~ObjectTreeModel()
{
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex & index) const
{
	if (!index.isValid())
	{
		return 0;
	}
	return QAbstractItemModel::flags(index);
}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return rootItem->data(section);
	}
	return QVariant();
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
	{
		return QModelIndex();
	}

	TreeItem* parentItem;

	if (!parent.isValid())
	{
		parentItem = rootItem.get();
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	TreeItem* child = parentItem->child(row);
	if (child)
	{
		return createIndex(row, column, child);
	}
	else
	{
		return QModelIndex();
	}
}

QModelIndex ObjectTreeModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
	{
		return QModelIndex();
	}

	TreeItem* child = static_cast<TreeItem*>(index.internalPointer());
	TreeItem* parentItem = child->parentItem();

	if (parentItem == rootItem.get())
	{
		return QModelIndex();
	}
	
	return createIndex(parentItem->row(), 0, parentItem);
}

int ObjectTreeModel::rowCount(const QModelIndex& parent) const
{
	TreeItem* parentItem;
	if (parent.column() > 0)
	{
		return 0;
	}

	if (!parent.isValid())
	{
		parentItem = rootItem.get();
	}
	else
	{
		parentItem = static_cast<TreeItem*>(parent.internalPointer());
	}

	return parentItem->childCount();
}

int ObjectTreeModel::columnCount(const QModelIndex& parent) const
{
	if (parent.isValid())
	{
		return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
	}
	return rootItem->columnCount();
}

QVariant ObjectTreeModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}

	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}

	TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
	
	return item->data(index.column());
}

bool ObjectTreeModel::insertRows(int row, int column, const QModelIndex & parent)
{
	return false;
}

void ObjectTreeModel::setupModelDataFromDB(const std::shared_ptr<DatabaseRef>& db)
{
	std::unordered_map<int, std::shared_ptr<Module>> map = db->GetMap();
	QList<QVariant> rootData;
	rootData << "Name" << "Type";
	rootItem = std::make_unique<TreeItem>(rootData);
}
