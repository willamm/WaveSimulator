#include "LShape.h"

template<typename T>
LShape<T>::LShape(const int x, const int y, const T vel)
	: mX(x)
	, mY(y)
	, mVel(vel)
{
}

template<typename T>
int LShape<T>::GetX() const
{
	return mX;
}

template<typename T>
int LShape<T>::GetY() const
{
	return mY;
}

template<typename T>
T LShape<T>::GetVel() const
{
	return mVel;
}

template class LShape<double>;
