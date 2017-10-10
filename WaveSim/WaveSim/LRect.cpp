#include "LRect.h"

template<typename T>
LRect<T>::LRect(int x, int y, int width, int height, T vel)
	: LShape(x, y, vel)
	, mWidth(width)
	, mHeight(height)
{
}

template<typename T>
void LRect<T>::Draw(QPainter* painter)
{
	painter->fillRect(LShape::GetX() * PIXEL_SIZE, LShape::GetY() * PIXEL_SIZE, mWidth * PIXEL_SIZE, mHeight * PIXEL_SIZE, QColor(255, 0, 0, 125));
}

template class LRect<double>;
