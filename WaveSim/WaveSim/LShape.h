#pragma once

#include <QColor>
#include <QPainter>
#include <qtreewidget.h>

#include "values.h"

template<typename T>
class LShape
{
public:
	LShape(const int x, const int y, const T vel);

	int GetX() const;
	int GetY() const;
	T GetVel() const;

	void SetX(int x);
	void SetY(int y);
	void SetVel(T vel);

	virtual void Draw(QPainter* painter) const = 0;

	virtual const std::string GetClassName() const = 0;

	virtual const int GetShapeType() const = 0;
private:
	int mX;
	int mY;
	T mVel;
};

