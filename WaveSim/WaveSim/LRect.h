#pragma once
#include "LShape.h"

template<typename T>
class LRect: public LShape<T>
{
public:
	LRect(const int x, const int y, const int width, const int height, const T vel);

	void Draw(QPainter* painter, const int pixelSize) const;

	const std::string GetClassName() const override;
	json GetJson() const override;

private:
	const int mWidth;
	const int mHeight;
};
