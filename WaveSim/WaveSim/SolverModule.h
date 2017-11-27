#pragma once

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
	const void ResetMaterials();
	const void ResetField();

	WaveSolver<double>* GetField();

	const void setNewSource(int x, int y);
	
private:
	WaveSolver<double> mSolver;
};