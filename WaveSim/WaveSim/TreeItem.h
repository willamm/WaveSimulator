#pragma once

#include <memory>
#include <vector>

#include <QStandardItem>

class TreeItem : public QStandardItem
{
public:
	TreeItem();
	TreeItem(const std::string& text);
	virtual ~TreeItem() = default;

	int type() const override;
	QVariant data(int role) const override;
	void setData(const QVariant& value, int role) override;
	QStandardItem* clone() const override;

private:
	std::vector<std::string> mColumnTitles;
	std::vector<int> mShapeData;
};

