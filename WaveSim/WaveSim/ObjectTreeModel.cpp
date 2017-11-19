#include "ObjectTreeModel.h"

ObjectTreeModel::ObjectTreeModel(const std::shared_ptr<DatabaseRef>& dbRef, QObject* parent)
	: QAbstractItemModel(parent)
{
	QList<QVariant> rootData;
	rootData << "Name" << "Type";
	rootItem = new TreeItem(rootData);

	QList<QVariant> dumbRoot;
	dumbRoot << "Root" << "Root";
	TreeItem* dumb = new TreeItem(dumbRoot, rootItem);

	setupModelDataFromDB(dbRef);
}
