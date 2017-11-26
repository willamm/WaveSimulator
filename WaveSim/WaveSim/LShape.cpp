#include "LShape.h"

template<typename T>
void LShape<T>::SetX(int x)
{
	mX = x;
}

template<typename T>
void LShape<T>::SetY(int y)
{
	mY = y;
}

template<typename T>
void LShape<T>::SetVel(T vel)
{
	mVel = vel;
}

template class LShape<double>;
