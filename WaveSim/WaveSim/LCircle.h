#pragma once
#include "LShape.h"

template<typename T>
class LCircle : public LShape<T>
{
public:
	LCircle(const int x, const int y, const int radius, const T vel)
		: LShape(x, y, vel)
		, mRadius(radius)
	{
	}

	int GetRadius() const
	{
		return mRadius;
	}

	void SetRadius(int radius)
	{
		mRadius = radius;
	}

	void Draw(QPainter* painter, const int pixelSize) const
	{
		int startingX = LShape::GetX() - mRadius;
		int startingY = LShape::GetY() - mRadius;

		painter->drawEllipse(startingX * pixelSize, startingY * pixelSize, 2 * mRadius * pixelSize, 2 * mRadius * pixelSize);
	}

	const std::string GetClassName() const override
	{
		return std::string("Circle");
	}

	json GetJson() const override
	{
		json output;

		output["Classname"] = "Circle";
		output["X"] = LShape::GetX();
		output["Y"] = LShape::GetY();
		output["Velocity"] = LShape::GetVel();
		output["Radius"] = mRadius;

		return output;
	}

private:
	int mRadius;
};