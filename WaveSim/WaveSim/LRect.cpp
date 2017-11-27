#include "LRect.h"

template<typename T>
LRect<T>::LRect(const int x, const int y, const int width, const int height, const T vel)
	: LShape(x, y, vel)
	, mWidth(width)
	, mHeight(height)
{
}

template<typename T>
void LRect<T>::Draw(QPainter* painter, const int pixelSize) const
{
	painter->fillRect(LShape::GetX() * pixelSize, LShape::GetY() * pixelSize, mWidth * pixelSize, mHeight * pixelSize, QColor(255, 0, 0, 125));
}

template<typename T>
const std::string LRect<T>::GetClassName() const
{	
	return std::string("Rectangle");
}

template<typename T>
int LRect<T>::GetWidth() const
{
	return mWidth;
}

template<typename T>
int LRect<T>::GetHeight() const
{
	return mHeight;
}

template<typename T>
void LRect<T>::SetWidth(int width)
{
	mWidth = width;
}

template<typename T>
void LRect<T>::SetHeight(int height)
{
	mHeight = height;
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
