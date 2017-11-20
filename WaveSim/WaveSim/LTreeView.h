#pragma once

#include <QMenu>
#include <QMouseEvent>
#include <QPoint>
#include <QTreeView>

class LTreeView : public QTreeView
{
	Q_OBJECT

public:
	LTreeView(QWidget* parent);
	~LTreeView() = default;

private:
	void displayMenu(const QMouseEvent* event);

	void mousePressEvent(QMouseEvent* event);
};
