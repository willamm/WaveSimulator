#include "LCircle.h"

template<typename T>
LCircle<T>::LCircle(const int x, const int y, const int radius, const T vel)
	: LShape(x, y, vel)
	, mRadius(radius)
{
}

template<typename T>
void LCircle<T>::Draw(QPainter* painter) const 
{
	int startingX = LShape::GetX() - mRadius;
	int startingY = LShape::GetY() - mRadius;

	painter->drawEllipse(startingX * PIXEL_SIZE, startingY * PIXEL_SIZE, 2 * mRadius * PIXEL_SIZE, 2 * mRadius * PIXEL_SIZE);
}

template class LCircle<double>;