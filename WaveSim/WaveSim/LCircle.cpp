#include "LCircle.h"

template<typename T>
LCircle<T>::LCircle(int x, int y, int radius, T vel)
	: LShape(x, y, vel)
	, mRadius(radius)
{
}

template<typename T>
void LCircle<T>::Draw(QPainter* painter) 
{
	int startingX = LShape::GetX() - mRadius;
	int startingY = LShape::GetY() - mRadius;

	painter->drawEllipse(startingX * PIXEL_SIZE, startingY * PIXEL_SIZE, 2 * mRadius * PIXEL_SIZE, 2 * mRadius * PIXEL_SIZE);
}

template class LCircle<double>;