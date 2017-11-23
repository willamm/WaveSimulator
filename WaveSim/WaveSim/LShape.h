#pragma once

#include <QColor>
#include <QPainter>

#include "json.hpp"

using json = nlohmann::json;

template<typename T>
class LShape
{
public:
	LShape(const int x, const int y, const T vel)
		: mX(x)
		, mY(y)
		, mVel(vel)
	{
	}

	inline int GetX() const
	{
		return mX;
	}

	inline int GetY() const
	{
		return mY;
	}

	inline T GetVel() const
	{
		return mVel;
	}

	virtual json GetJson() const = 0;

	virtual void Draw(QPainter* painter, const int pixelSize) const = 0;

	virtual const std::string GetClassName() const = 0;
private:
	const int mX;
	const int mY;
	const T mVel;
};

