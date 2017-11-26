#pragma once
#include "LShape.h"

template<typename T>
class LRect: public LShape<T>
{
public:
	LRect(const int x, const int y, const int width, const int height, const T vel);

	void Draw(QPainter* painter) const override;

	const std::string GetClassName() const override;

	const int GetShapeType() const override;

	int GetWidth() const;
	int GetHeight() const;

	void SetWidth(int width);
	void SetHeight(int height);

private:
	int mWidth;
	int mHeight;
};
