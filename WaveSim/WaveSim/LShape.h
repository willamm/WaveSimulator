#pragma once

#include <QColor>
#include <QPainter>

#include "values.h"
#include "json.hpp"

using json = nlohmann::json;

template<typename T>
class LShape
{
public:
	LShape(const int x, const int y, const T vel);

	int GetX() const;
	int GetY() const;
	T GetVel() const;
	virtual json GetJson() const = 0;

	virtual void Draw(QPainter* painter) const = 0;

	virtual const std::string GetClassName() const = 0;
private:
	const int mX;
	const int mY;
	const T mVel;
};

