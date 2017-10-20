#pragma once

#include <QColor>
#include <QPainter>

#include "values.h"

template<typename T>
class LShape
{
public:
	LShape(const int x, const int y, const T vel);

	int GetX() const;
	int GetY() const;
	T GetVel() const;

	virtual void Draw(QPainter* painter) = 0 const;
private:
	const int mX;
	const int mY;
	const T mVel;
};

