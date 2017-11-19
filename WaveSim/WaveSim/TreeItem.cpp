#include "TreeItem.h"

TreeItem::TreeItem(const std::string& itemName, const std::vector<int>& shapeData, std::weak_ptr<TreeItem>& parent)
	: m_itemName(itemName)
	, m_itemData(shapeData)
	, m_parentItem(parent)
{
}
