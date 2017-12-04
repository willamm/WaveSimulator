#pragma once

#include "LShape.h"

template<typename T>
class LRect : public LShape<T>
{
public:

	/**
	*	Contructor.
	*
	*	Creates a data objec that represents a rectangle. The retangle is specified by its top left corner,
	*	its width, and its height.
	*	
	*	@param x The x position of the top left corner.
	*	@param y The y position of the top left corner.
	*	@param width The width of the rectangle.	
	*	@param height The height of the rectangle.
	*	@param vel The velocity of the rectangle.
	*/
	LRect(const int x, const int y, const int width, const int height, const T vel)
		: LShape(x, y, vel)
		, mWidth(width)
		, mHeight(height)
	{
	}

	/**
	*	Accessor method for height.
	*
	*	@return The rectangle's height.
	*/
	int GetWidth() const
	{
		return mWidth;
	}

	/**
	*	Accessor method for width.
	*
	*	@return The rectangle's width.
	*/
	int GetHeight() const
	{
		return mHeight;
	}

	/**
	*	Modifier method for width.
	*	
	*	@param x The new width.
	*/
	void SetWidth(int width)
	{
		mWidth = width;
	}

	/**
	*	Modifier method for height.
	*	
	*	@param x The new height.
	*/
	void SetHeight(int height)
	{
		mHeight = height;
	}

	/**
	*	Changes the values of the shape to new values
	*
	*	The new paramaters are entered in the range of [1, X][1, Y] but get 
	*	converted to [0, X-1][0, Y-1] where X and Y are the width and height 
	*	of the solver.
	*	
	*	@param x The new x position.
	*	@param y The new y position.
	*	@param width The new width.
	*	@param height The new height.
	*	@param vel The new velocity.
	*/
	void SetNewParams(const int x, const int y, const int width, const int height, const double vel)
	{
		LShape::SetX(x - 1);
		LShape::SetY(y - 1);
		LShape::SetVel(vel);
		mWidth = width;
		mHeight = height;
	}

	/**
	*	Draws the rectangle.
	*
	*	Draws the shape on a QPainter surface.
	*
	*	@param painter The painter to paint the shape on.
	*	@param pixelSize The size one cell(pixel) in the solver should be drawn as.
	*/
	void Draw(QPainter* painter, const int pixelSize) const
	{
		painter->fillRect(LShape::GetX() * pixelSize, LShape::GetY() * pixelSize, mWidth * pixelSize, mHeight * pixelSize, QColor(255, 0, 0, 125));
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
		return std::string("Rectangle");
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

		output["Classname"] = "Rectangle";
		output["X"] = LShape::GetX();
		output["Y"] = LShape::GetY();
		output["Velocity"] = LShape::GetVel();
		output["Width"] = mWidth;
		output["Height"] = mHeight;

		return output;
	}

private:

	int mWidth;		/*! The width of the rectangle. */
	int mHeight;	/*! The height of the rectangle. */
};
