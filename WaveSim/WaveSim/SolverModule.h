#pragma once

#include <vector>

#include "LShape.h"
#include "LRect.h"
#include "LCircle.h"
#include "Module.h"
#include "WaveSolver.h"

using namespace std;

class SolverModule final : public Module
{
public:
	SolverModule();
	~SolverModule() = default;

	shared_ptr<WaveSolver<double>> GetSolver() const;

	const void AddRectangle(const int x, const int y, const int width, const int height, const double vel);
	const void AddCircle(const int x, const int y, const int radius, const double vel);
	const void RepopulateShapes(const vector<unique_ptr<LShape<double>>>& shapes);
	const void ResetMaterials();
	const void ResetField();

	WaveSolver<double>* GetField();

	const void SetNewSource(int x, int y);
	
private:
	WaveSolver<double> mSolver;	/*! The phyics engine. */
};