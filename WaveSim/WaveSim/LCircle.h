#pragma once

#include "LShape.h"

template<typename T>
class LCircle : public LShape<T>
{
public:

	/**
	*	Contructor.
	*
	*	Creates a data objec that represents a circle. The circle is specified by its center, and radius.
	*	
	*	@param x The x position of the center.
	*	@param y The y position of the center.
	*	@param radius The radius of the circle.
	*	@param vel The velocity of the circle.
	*/
	LCircle(const int x, const int y, const int radius, const T vel)
		: LShape(x, y, vel)
		, mRadius(radius)
	{
	}

	/**
	*	Accessor method for radius.
	*
	*	@return The circle's radius.
	*/
	int GetRadius() const
	{
		return mRadius;
	}

	/**
	*	Modifier method for radius.
	*	
	*	@param x The new radius.
	*/
	void SetRadius(int radius)
	{
		mRadius = radius;
	}

	/**
	*	Draws the circle.
	*
	*	Draws the shape on a QPainter surface.
	*
	*	@param painter The painter to paint the shape on.
	*	@param pixelSize The size one cell(pixel) in the solver should be drawn as.
	*/
	void Draw(QPainter* painter, const int pixelSize) const
	{
		int startingX = LShape::GetX() - mRadius;
		int startingY = LShape::GetY() - mRadius;

		painter->drawEllipse(startingX * pixelSize, startingY * pixelSize, 2 * mRadius * pixelSize, 2 * mRadius * pixelSize);
	}

	/**
	*	Returns the name of the class.
	*
	*	Gives the name of the class in case it needs to be known during runtime.
	*
	*	@return The name of the class.
	*/
	const std::string GetClassName() const override
	{
		return std::string("Circle");
	}

	/**
	*	Serialize the object to json.
	*	This is a virtual method.
	*
	*	Converts all fields of the shape to a json obect. The main purpose of this is so that
	*	the shape can be saved to a file.
	*
	*	@return A json representaiton of the shape.
	*/
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
	int mRadius; /*! The radius of the circle. */
};