#include "LShape.h"

template<typename T>
LShape<T>::LShape(int x, int y, T vel)
	: mX(x)
	, mY(y)
	, mVel(vel)
{
}

template<typename T>
int LShape<T>::GetX()
{
	return mX;
}

template<typename T>
int LShape<T>::GetY()
{
	return mY;
}

template<typename T>
T LShape<T>::GetVel()
{
	return mVel;
}

template class LShape<double>;
