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

template<typename T>
const int LShape<T>::GetShapeType() const
{
	const int shapeType = QTreeWidgetItem::UserType;
	return shapeType;
}

template class LShape<double>;
