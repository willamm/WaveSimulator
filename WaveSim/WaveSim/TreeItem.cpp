#include "TreeItem.h"

TreeItem::TreeItem()
	: QStandardItem()
{
}

TreeItem::TreeItem(const std::string& text)
	: QStandardItem(QString::fromStdString(text))
{
	mColumnTitles.push_back(text);
}

int TreeItem::type() const
{
	return QStandardItem::UserType + 1;
}

QVariant TreeItem::data(int role) const
{
	if (role == Qt::DisplayRole)
	{
		return QString::fromStdString(mColumnTitles.at(0));
	}
	if (role == Qt::ToolTipRole)
	{
		return QString();
	}
	return QVariant();
}

void TreeItem::setData(const QVariant& value, int role)
{
	QStandardItem::setData(value, role);
}

QStandardItem* TreeItem::clone() const
{
	return new TreeItem();
}
