#include "SolverModule.h"

using namespace std;

/**
 *	Constructor for SolverModule.
 *
 *	The solver module holds a WaveSolver object and contains all the accessor methods related to it.
 *	The Solvermodule starts off being stored online in the DatabaseRef singleton class, but is passed
 *	to other controller classes as needed.
*/
SolverModule::SolverModule()
	: mSolver(WaveSolver<double>(X, Y))
{
}

/**
 *	GetSolver()
 *	
 *  Gets the WaveSolver
 *
 *	Returns a shared pointer to the current WaveSolver
*/
shared_ptr<WaveSolver<double>> SolverModule::GetSolver() const
{
	return shared_ptr<WaveSolver<double>>();
}

/**
 *	AddRectangle(const int x, const int y, const int width, const int height, const double vel)
 *		x:		The x coordinate of the top left corner of the rectangle to be added
 *		y:		The y coordinate of the top left corner of the rectangle to be added
 *		width:	The width of the rectangle to be added
 *		height:	The height of the rectangle to be added
 *		vel:	The amount of influence the shape will have over its area, 1 having no effect and 0 completely
 *				blocking all movement
 *
 *	Addes a rectangle to the current WaveSovler
*/
const void SolverModule::AddRectangle(const int x, const int y, const int width, const int height, const double vel)
{
	mSolver.addRectangle(x, y, x + width, y + height, vel);
}


/**
 *	AddCircle(const int x, const int y, const int radius, const int vel)
 *		x:		The x coordinate of the center of the circle to be added
 *		y:		The y coordinate of the center of the rectangle to be added
 *		radius:	The radius of the circle to be added
 *		vel:	The amount of influence the shape will have over its area, 1 having no effect and 0 completely
 *				blocking all movement
 *
 *	Addes a rectangle to the current WaveSovler
*/
const void SolverModule::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolver.addCircle(x, y, radius, vel);
}

/**
 *	ResetMaterials()
 *
 *	Removes all the shapes from the current WaveSolver but leaves the current simulation running
*/
const void SolverModule::ResetMaterials()
{
	mSolver.resetMaterials();
}

/**
 *	ResetField()
 *
 *	Sets the field back to the initial poisitoin but leaves all shapes
*/
const void SolverModule::ResetField()
{
	mSolver.resetField();
}

/**
 *	GetField()
 *
 *	Returns a raw pointer to field of the current WaveSolver
*/
WaveSolver<double>* SolverModule::GetField()
{
	return &mSolver;
}
