#include "ShapesModule.h"

using namespace std;

/**
 *	Constructor for ShapesModule.
 *
 *	The shapes module holds a vector of LShape data objects. This class does not affect the WaveSolver,
 *	this class is to store shapes so that the object tree can know what is currently in the solver.
 *	The ShapesModule starts off being stored online in the DatabaseRef singleton class, but is passed
 *	to other controller classes as needed.
*/
ShapesModule::ShapesModule()
	: mShapes(vector<unique_ptr<LShape<double>>>())
{
}

/**
 *	AddRect(const int x, const int y, const int w, const int h, const double vel)
 *	
 *	@param x The x location of the top left corner of the LRect to be added
 *	@param y The y location of the top left corner of the LRect to be added
 *	@param w The width of the LRect to be added
 *	@param h The height of the LRect to be added
 *	@param vel The velocity of squares covered by the LRect to be added, 1 is full velocity and 0 is no movement
 *
 *	Adds a LRect to the vector of LShapes. 
 *
 *  Returns a boolean based on if the LRect was added successfully
*/
const bool ShapesModule::AddRect(const int x, const int y, const int w, const int h, const double vel)
{
	int initSize = mShapes.size();
	mShapes.push_back(make_unique<LRect<double>>(x, y, w, h , vel));
	int postSize = mShapes.size();
	return postSize > initSize;
}

/**
 *	AddCircle(const int x, const int y, const int r, const double vel)
 *  @param x The x location of the center of the LCircle	
 *	@param y The y location of the center of the LCircle	
 *	@param r The radius of the LCircle to be added
 *	@param vel	The velocity of squares covered by the LCircle to be added, 1 is full velocity and 0 is no movement
 *
 *	Adds a LCircle to the vector of LShapes. 
 *
 *  Returns a boolean based on if the LCircle was added successfully
*/
const bool ShapesModule::AddCircle(const int x, const int y, const int r, const double vel)
{
	int initSize = mShapes.size();
	mShapes.push_back(make_unique<LCircle<double>>(x, y, r, vel));
	int postSize = mShapes.size();
	return false;
}

/**
 *	GetShapes()
 *
 *	Gives a reference to the vector of LShapes so that the shapes can be read. 
 *
 *  Returns a const reference to the current vector of LShapes
*/
const vector<unique_ptr<LShape<double>>>& ShapesModule::GetShapes() const
{
	return mShapes;
}

/**
 *	ClearAllShapes()
 *
 *  Removes all LShapes in the LShapes vector
 *
 *	Returns true if the vector was cleared properly
*/
const bool ShapesModule::ClearAllShapes()
{
	mShapes.clear();
	return mShapes.empty();
}


/**
 *	GetJson()
 *
 *  Parses shape data and adds to a json object
 *
 *	Returns the json object that the shapes were parsed to
*/
json ShapesModule::GetJson()
{
	json output;
	int numShapes = 0;

	for (auto it = mShapes.begin(); it != mShapes.end(); ++it)
	{
		//TODO: parse shapes to JSON
		json tempShapeObject = (*it)->GetJson();

		output[numShapes] = tempShapeObject;

		numShapes++;
	}

	return output;
}


/**
 *	LoadJson()
 *
 *  Parses a json object and loads that data to the shapes module
 *
 *	Returns true if succesful, otherwise returns false
*/
const bool ShapesModule::LoadJson(json inputFromFile)
{
	//TODO: READ DATA INTO SHAPES MODULE
	return false;
}