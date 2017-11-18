#pragma once

#include "TreeItem.h"
#include "DatabaseRef.h"

#include <QAbstractItemModel>
#include <QStringList>

class ObjectTreeModel : public QAbstractItemModel // TODO: extend QStandardItemModel instead?
{
	Q_OBJECT

public:
	explicit ObjectTreeModel(const std::shared_ptr<DatabaseRef>& dbRef, QObject* parent = 0);
	~ObjectTreeModel();

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	bool insertRows(int row, int column, const QModelIndex& parent = QModelIndex()) override;

public slots:
	
	
private:
	void setupModelDataFromDB(const std::shared_ptr<DatabaseRef>& dbRef);

	std::unique_ptr<TreeItem> rootItem;
};
