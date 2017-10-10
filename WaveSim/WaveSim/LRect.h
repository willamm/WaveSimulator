#pragma once
#include "LShape.h"

template<typename T>
class LRect:
	public LShape<T>
{
public:
	LRect(int x, int y, int width, int height, T vel);

	void Draw(QPainter* painter);

private:
	int mWidth;
	int mHeight;
};
