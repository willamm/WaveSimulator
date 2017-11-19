#pragma once

#include <memory>
#include <vector>

class TreeItem 
{
public:
	explicit TreeItem(const std::string& itemName, const std::vector<int>& shapeData, std::weak_ptr<TreeItem>& parent);
	virtual ~TreeItem() = default;

	void appendChild(std::unique_ptr<TreeItem> child);

	TreeItem* child(int row);
	int childCount() const;
	int columnCount() const;
	std::pair<std::string, std::vector<int>> itemData(int column) const;
	int row() const;
	std::weak_ptr<TreeItem> parentItem();
	
private:
	std::vector<std::unique_ptr<TreeItem>> m_childItems;
	std::string m_itemName;
	std::vector<int> m_itemData;
	std::weak_ptr<TreeItem> m_parentItem;
};

