#pragma once
#include "LShape.h"

template<typename T>
class LCircle :
	public LShape<T>
{
public:
	LCircle(const int x, const int y, const int radius, const T vel);

	void Draw(QPainter* painter) const;

private:
	const int mRadius;
};