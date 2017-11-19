#include "TreeItem.h"

TreeRow::TreeRow(const std::vector<std::string>& itemNames, const std::vector<int>& shapeData)
	: m_rowStrings(itemNames)
	, m_shapeData(shapeData)
{
}

void TreeRow::appendChild(std::unique_ptr<TreeRow> child)
{
	m_childItems.push_back(std::move(child));
}

TreeRow* TreeRow::child(int row)
{
	return m_childItems.at(row).get();
}

int TreeRow::childCount() const
{
	return m_childItems.size();
}

int TreeRow::columnCount() const
{
	return 0;
}

std::pair<std::string, std::vector<int>> TreeRow::itemData(int column) const
{
	return std::pair<std::string, std::vector<int>>();
}

int TreeRow::row() const
{
	return 0;
}

std::weak_ptr<TreeRow> TreeRow::parentItem()
{
	return m_parentItem;
}
