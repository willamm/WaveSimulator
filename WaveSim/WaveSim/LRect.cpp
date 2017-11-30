#include "LRect.h"

template<typename T>
void LRect<T>::Draw(QPainter* painter, const int pixelSize) const
{
	painter->fillRect(LShape::GetX() * pixelSize, LShape::GetY() * pixelSize, mWidth * pixelSize, mHeight * pixelSize, QColor(255, 0, 0, 125));
}

template<typename T>


template<typename T>
json LRect<T>::GetJson() const
{
}

template class LRect<double>;
