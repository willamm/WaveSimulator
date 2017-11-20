#pragma once

#include <memory>
#include <vector>

class TreeRow : public std::enable_shared_from_this<TreeRow>
{
public:
	TreeRow(std::weak_ptr<TreeRow> parent = std::weak_ptr<TreeRow>());
	TreeRow(std::vector<std::string> columnTitles, std::weak_ptr<TreeRow> parent = std::weak_ptr<TreeRow>());
	virtual ~TreeRow() = default;

	// Accessors
	const std::shared_ptr<TreeRow>& getChild(int row) const;
	const std::vector<int>& getShapeData() const;
	const std::vector<std::string>& getRowStrings() const;
	const std::shared_ptr<TreeRow> getParentItem() const;

	// Mutators
	void setRowStrings(const std::vector<std::string>& rowStrings);
	void setShapeData(const std::vector<int>& shapeData);
	void appendChild(const std::shared_ptr<TreeRow>& child);

	int childCount() const;
	int columnCount() const;
	int row() const;
	
	
	
private:
	const int childPosition(const std::shared_ptr<const TreeRow>& child) const;

	std::vector<std::shared_ptr<TreeRow>> m_childItems;
	std::vector<std::string> m_rowStrings;
	std::vector<int> m_shapeData;
	std::weak_ptr<TreeRow> m_parentItem;
};

