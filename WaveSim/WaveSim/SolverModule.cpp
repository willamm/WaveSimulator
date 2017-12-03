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
	: mSolver(WaveSolver<double>(200, 200))
{
	// TODO: Get the size from SettingsManager
}

/**
 *	Get the Wave Solver
 *	
 *	Gets a shared_ptr to the current wave solver.
 *
 *	@return A shared pointer to the current WaveSolver
*/
shared_ptr<WaveSolver<double>> SolverModule::GetSolver() const
{
	return shared_ptr<WaveSolver<double>>();
}

/**
 *	Adds a rectangle to the solver.
 *
 *	Adds a rectangle where the user specifies the top left corner, the width, and the height.
 *	The user specifies parameters in a range of [1, X][1, Y] where X and Y are the width and the height of the field.
 *	The function will convert the shape to fit on a range of [0, X-1][0, Y-1] by subtracting 1 from the x and y position of the circle.
 *
 *	@param x The x coordinate of the top left corner of the rectangle to be added
 *	@param y The y coordinate of the top left corner of the rectangle to be added
 *	@param width The width of the rectangle to be added
 *	@param height The height of the rectangle to be added
 *	@param vel The amount of influence the shape will have over its area, 1 having no effect and 0 completely
 *				blocking all movement
*/
const void SolverModule::AddRectangle(const int x, const int y, const int width, const int height, const double vel)
{
	mSolver.addRectangle(x - 1, y - 1, x + width, y + height, vel);
}


/**
 *	Adds a circle to the solver.
 *
 *	Adds a circle where the user specifies the center and the radius.
 *	The user specifies parameters in a range of [1, X][1, Y] where X and Y are the width and the height of the field.
 *	The function will convert the shape to fit on a range of [0, X-1][0, Y-1] by subtracting 1 from the x and y position of the circle.
 *
 *	@param x: The x coordinate of the center of the circle to be added
 *	@param y: The y coordinate of the center of the rectangle to be added
 *	@param radius:	The radius of the circle to be added
 *	@param vel: The amount of influence the shape will have over its area, 1 having no effect and 0 completely blocking all movement
*/
const void SolverModule::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolver.addCircle(x - 1, y - 1, radius, vel);
}

const void SolverModule::RepopulateShapes(const vector<unique_ptr<LShape<double>>>& shapes)
{
	// Delete current WaveSim
	// Iterate through shapes and add
}

/**
 *	Removes all shapes
 *
 *	Removes all the shapes from the current WaveSolver but leaves the current simulation running
*/
const void SolverModule::ResetMaterials()
{
	mSolver.resetMaterials();
}

/**
 *	Reset field.
 *
 *	Sets the field back to the initial poisitoin but leaves all shapes
*/
const void SolverModule::ResetField()
{
	mSolver.resetField();
}

/**
 *	Gets the field
 *
 *	Returns a raw pointer to field of the current WaveSolver
*/
WaveSolver<double>* SolverModule::GetField()
{
	return &mSolver;
}

/**
 *	Sets a new source of wave propgeation.
 *
 *	Creates a new source and removes the old soure.
*/
const void SolverModule::SetNewSource(int x, int y)
{
	mSolver.setNewSource(x, y);
}