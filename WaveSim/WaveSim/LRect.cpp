#include "LRect.h"

template<typename T>
LRect<T>::LRect(const int x, const int y, const int width, const int height, const T vel)
	: LShape(x, y, vel)
	, mWidth(width)
	, mHeight(height)
{
}

template<typename T>
void LRect<T>::Draw(QPainter* painter) const
{
	painter->fillRect(LShape::GetX() * PIXEL_SIZE, LShape::GetY() * PIXEL_SIZE, mWidth * PIXEL_SIZE, mHeight * PIXEL_SIZE, QColor(255, 0, 0, 125));
}

template<typename T>
const std::string LRect<T>::GetClassName() const
{	
	return std::string("Rectangle");
}

template<typename T>
json LRect<T>::GetJson() const
{
	json output;

	output["Classname"] = "Rectangle";
	output["X"] = LShape::GetX();
	output["Y"] = LShape::GetY();
	output["Velocity"] = LShape::GetVel();
	output["Width"] = mWidth;
	output["Height"] = mHeight;
	return output;
}

template class LRect<double>;
