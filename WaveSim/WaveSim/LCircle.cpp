#include "LCircle.h"

template<typename T>
LCircle<T>::LCircle(const int x, const int y, const int radius, const T vel)
	: LShape(x, y, vel)
	, mRadius(radius)
{
}

template<typename T>
int LCircle<T>::GetRadius() const
{
	return mRadius;
}

template<typename T>
void LCircle<T>::SetRadius(int radius)
{
	mRadius = radius;
}

template<typename T>
void LCircle<T>::Draw(QPainter* painter, const int pixelSize) const 
{
	int startingX = LShape::GetX() - mRadius;
	int startingY = LShape::GetY() - mRadius;

	painter->drawEllipse(startingX * pixelSize, startingY * pixelSize, 2 * mRadius * pixelSize, 2 * mRadius * pixelSize);
}

template<typename T>
const std::string LCircle<T>::GetClassName() const
{
	return std::string("Circle");
}

template<typename T>
json LCircle<T>::GetJson() const
{
	json output;

	output["Classname"] = "Circle";
	output["X"] = LShape::GetX();
	output["Y"] = LShape::GetY();
	output["Velocity"] = LShape::GetVel();
	output["Radius"] = mRadius;
	return output;
}

template class LCircle<double>;