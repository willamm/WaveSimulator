#include "LTreeView.h"

#include <QDebug>

LTreeView::LTreeView(QWidget *parent)
	: QTreeView(parent)
{
}

void LTreeView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		displayMenu(event);
	}
}

void LTreeView::displayMenu(const QMouseEvent* event)
{
	QWidget child(childAt(event->pos()));

	QMenu* menu = new QMenu(this);
	menu->addAction("New menu");
	menu->popup(event->globalPos());
}