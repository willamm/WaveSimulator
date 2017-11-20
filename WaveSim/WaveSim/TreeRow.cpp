#include "TreeRow.h"

TreeRow::TreeRow(std::weak_ptr<TreeRow> parent)
	: m_parentItem(parent)
{
}

TreeRow::TreeRow(std::vector<std::string> columnTitles, std::weak_ptr<TreeRow> parent)
	: m_parentItem(parent)
	, m_rowStrings(columnTitles)
{
}

void TreeRow::setRowStrings(const std::vector<std::string>& rowStrings)
{
	m_rowStrings = rowStrings;
}

void TreeRow::setShapeData(const std::vector<int>& shapeData)
{
	m_shapeData = shapeData;
}

/**
* Appends a child to this row, which makes this row the parent of the child row.
*
* @param child Shared pointer to a TreeRow containing the child element.
* @param columnTitles Vector containing the strings that will be displayed in the view.
*/
void TreeRow::appendChild(const std::shared_ptr<TreeRow>& child)
{
	m_childItems.emplace_back(std::make_shared<TreeRow>(TreeRow::shared_from_this()));
}

const std::shared_ptr<TreeRow>& TreeRow::getChild(int row) const
{
	return m_childItems.at(row);
}

int TreeRow::childCount() const
{
	return m_childItems.size();
}

int TreeRow::columnCount() const
{
	return m_rowStrings.size();
}

const std::vector<int>& TreeRow::getShapeData() const
{
	return m_shapeData;
}

const std::vector<std::string>& TreeRow::getRowStrings() const
{
	return m_rowStrings;
}

/**
* Gets the row in the model that this object occupies.
*
* @return The position of this row in the model.
*/
int TreeRow::row() const
{
	if (m_parentItem.expired())
	{
		return 0;
	}
	return m_parentItem.lock()->childPosition(TreeRow::shared_from_this());
}

const int TreeRow::childPosition(const std::shared_ptr<const TreeRow>& child) const
{
	auto iter = std::find(m_childItems.begin(), m_childItems.end(), child);
	if (iter != m_childItems.end())
	{
		return iter - m_childItems.begin();
	}
	// Required by Qt
	return -1;
}

const std::shared_ptr<TreeRow> TreeRow::getParentItem() const
{
	return m_parentItem.lock();
}
