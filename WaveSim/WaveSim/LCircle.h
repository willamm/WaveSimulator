#pragma once
#include "LShape.h"

template<typename T>
class LCircle :
	public LShape<T>
{
public:
	LCircle(int x, int y, int radius, T vel);

	void Draw(QPainter* painter);

private:
	int mRadius;
};