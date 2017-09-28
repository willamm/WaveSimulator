#pragma once

#include "TreeItem.h"

#include <QAbstractItemModel>

class ObjectTreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit ObjectTreeModel(const QString& data, QObject* parent = 0);
	~ObjectTreeModel();

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

private:
	void setupModelData(const QStringList& lines, TreeItem* parent);

	TreeItem* rootItem;
};
