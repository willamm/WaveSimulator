#pragma once

#include <QColor>
#include <QPainter>
#include <QTreeWidget>

#include "json.hpp"

using json = nlohmann::json;

template<typename T>
class LShape
{
public:

	/**
	*	Contructor.
	*	This class is abstract.	
	*
	*	Creates a data object that represents all shapes and represents position and velocity.
	*
	*	@param x The x position.
	*	@param y The y position.
	*	@param vel The velocity of the shape.
	*/
	LShape(const int x, const int y, const T vel)
		: mX(x)
		, mY(y)
		, mVel(vel)
	{
	}

	/**
	*	Accessor method for X position.
	*
	*	@return The shape's X position.
	*/
	inline int GetX() const
	{
		return mX;
	}

	/**
	*	Accessor method for Y position.
	*
	*	@return The shape's Y position.
	*/
	inline int GetY() const
	{
		return mY;
	}

	/**
	*	Accessor method for the velocity. 
	*
	*	@return The shape's velocity.
	*/
	inline T GetVel() const
	{
		return mVel;
	}

	/**
	*	Modifier method for X position.
	*	
	*	@param x The new x position.
	*/
	inline void SetX(int x)
	{
		mX = x;
	}

	/**
	*	Modifier method for Y position.
	*	
	*	@param y The new y position.
	*/
	inline void SetY(int y)
	{
		mY = y;
	}

	/**
	*	Modifier method for the velocity.
	*	
	*	@param vel The new velocity.
	*/
	inline void SetVel(T vel)
	{
		mVel = vel;
	}

	/**
	*	Draws the shape.
	*	This is an virtual method.
	*
	*	Draws the shape on a QPainter surface.
	*
	*	@param painter The painter to paint the shape on.
	*	@param pixelSize The size one cell(pixel) in the solver should be drawn as.
	*/
	virtual void Draw(QPainter* painter, const int pixelSize) const = 0;

	/**
	*	Returns the name of the class.
	*	This is an virtual method.
	*
	*	Gives the name of the class in case it needs to be known during runtime.
	*
	*	@return The name of the class.
	*/
	virtual const std::string GetClassName() const = 0;

	/**
	*	Serialize the object to json.
	*	This is a virtual method.
	*
	*	Converts all fields of the shape to a json obect. The main purpose of this is so that
	*	the shape can be saved to a file.
	*
	*	@return A json representaiton of the shape.
	*/
	virtual json GetJson() const = 0;

private:

	int mX;	/*! The shapes x position. */
	int mY;	/*! The shapes y position. */
	T mVel; /*! The velocity modifier of the shape, 0 means no movement and 1 means full movement. */
};