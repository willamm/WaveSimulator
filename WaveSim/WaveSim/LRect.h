#pragma once
#include "LShape.h"

template<typename T>
class LRect : public LShape<T>
{
public:
	LRect(const int x, const int y, const int width, const int height, const T vel)
		: LShape(x, y, vel)
		, mWidth(width)
		, mHeight(height)
	{
	}

	int GetWidth() const
	{
		return mWidth;
	}

	int GetHeight() const
	{
		return mHeight;
	}

	void SetWidth(int width)
	{
		mWidth = width;
	}

	void SetHeight(int height)
	{
		mHeight = height;
	}

	void Draw(QPainter* painter, const int pixelSize) const
	{
		painter->fillRect(LShape::GetX() * pixelSize, LShape::GetY() * pixelSize, mWidth * pixelSize, mHeight * pixelSize, QColor(255, 0, 0, 125));
	}

	const std::string GetClassName() const override
	{
		return std::string("Rectangle");
	}

	json GetJson() const override
	{
		json output;

		output["Classname"] = "Rectangle";
		output["X"] = LShape::GetX();
		output["Y"] = LShape::GetY();
		output["Velocity"] = LShape::GetVel();
		output["Width"] = mWidth;
		output["Height"] = mHeight;

		return output;
	}

private:
	int mWidth;
	int mHeight;
};
