#pragma once
#include "LShape.h"

template<typename T>
class LCircle: public LShape<T>
{
public:
	LCircle(const int x, const int y, const int radius, const T vel);

	int GetRadius() const;
	void SetRadius(int radius);

	void Draw(QPainter* painter, const int pixelSize) const;
	const std::string GetClassName() const override;
	json GetJson() const override;

private:
	int mRadius;
};