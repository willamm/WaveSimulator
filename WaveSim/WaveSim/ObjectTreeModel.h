#pragma once

#include "TreeRow.h"
#include "DatabaseRef.h"

#include <QAbstractItemModel>
#include <QStringList>

class ObjectTreeModel : public QAbstractItemModel 
{
	Q_OBJECT

public:
	explicit ObjectTreeModel(QObject* parent = 0);
	~ObjectTreeModel() = default;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role) const override;

	const std::shared_ptr<TreeRow>& getRoot() const;

	void addRow(const QModelIndex& index, const std::shared_ptr<TreeRow> child);
public slots:
	void addShapeToTree();
	
private:
	void setupModelDataFromDB(const std::shared_ptr<DatabaseRef>& dbRef);

	std::shared_ptr<TreeRow> m_rootItem;
	std::shared_ptr<TreeRow> m_geometryRootItem;
	std::shared_ptr<TreeRow> m_solverRootItem;
};
