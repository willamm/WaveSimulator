#include "ObjectTreeModel.h"

ObjectTreeModel::ObjectTreeModel(const std::shared_ptr<DatabaseRef>& dbRef, QObject* parent)
	: QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Name" << "Type";
	rootItem = std::make_unique<TreeRow>("Root", std::vector<int>());

	setupModelDataFromDB(dbRef);
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex & index) const
{
	return Qt::ItemFlags();
}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex & parent) const
{
	return QModelIndex();
}

QModelIndex ObjectTreeModel::parent(const QModelIndex & index) const
{
	return QModelIndex();
}

int ObjectTreeModel::rowCount(const QModelIndex & parent) const
{
	return 0;
}

int ObjectTreeModel::columnCount(const QModelIndex & parent) const
{
	return 0;
}

QVariant ObjectTreeModel::data(const QModelIndex & index, int role) const
{
	return QVariant();
}

bool ObjectTreeModel::insertRows(int row, int column, const QModelIndex & parent)
{
	return false;
}

void ObjectTreeModel::setupModelDataFromDB(const std::shared_ptr<DatabaseRef>& dbRef)
{

}

void ObjectTreeModel::addShapeToTree()
{

}
