#pragma once

#include <QColor>
#include <QPainter>

#include "values.h"

template<typename T>
class LShape
{
public:
	LShape(int x, int y, T vel);

	int GetX();
	int GetY();
	T GetVel();

	virtual void Draw(QPainter* painter) = 0;
private:
	int mX;
	int mY;
	T mVel;
};

