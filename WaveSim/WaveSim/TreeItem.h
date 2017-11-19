#pragma once

#include <memory>
#include <vector>

class TreeRow 
{
public:
	explicit TreeRow(const std::vector<std::string>& rowStrings, const std::vector<int>& shapeData);
	virtual ~TreeRow() = default;

	void appendChild(std::unique_ptr<TreeRow> child);

	TreeRow* child(int row);
	int childCount() const;
	int columnCount() const;
	std::pair<std::string, std::vector<int>> itemData(int column) const;
	int row() const;
	std::weak_ptr<TreeRow> parentItem();
	
private:
	std::vector<std::unique_ptr<TreeRow>> m_childItems;
	std::vector<std::string> m_rowStrings;
	std::vector<int> m_shapeData;
	std::weak_ptr<TreeRow> m_parentItem;
};

