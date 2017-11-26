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
const int LRect<T>::GetShapeType() const
{
	return LShape<T>::GetShapeType() + 1;
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

template class LRect<double>;
