#include "SolverModule.h"

using namespace std;

SolverModule::SolverModule()
	: mSolver(WaveSolver<double>(X, Y))
{
}

shared_ptr<WaveSolver<double>> SolverModule::GetSolver() const
{
	return shared_ptr<WaveSolver<double>>();
}

const void SolverModule::AddRectangle(const int x, const int y, const int width, const int height, const double vel)
{
	mSolver.addRectangle(x, y, x + width, y + height, vel);
}

const void SolverModule::AddCircle(const int x, const int y, const int radius, const double vel)
{
	mSolver.addCircle(x, y, radius, vel);
}

const void SolverModule::ResetMaterials()
{
	mSolver.resetMaterials();
}

const void SolverModule::ResetField()
{
	mSolver.resetField();
}

WaveSolver<double>* SolverModule::GetField()
{
	return &mSolver;
}
