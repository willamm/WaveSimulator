#pragma once
#include <memory>
#include <unordered_map>

#include <Module.h>
#include <ShapesModule.h>
#include <SolverModule.h>

using namespace std;

class DatabaseRef final
{
public:
	DatabaseRef();
	~DatabaseRef() = default;

	shared_ptr<Module> GetModule(const int key) const;

	const unordered_map<int, shared_ptr<Module>>& GetMap() const;

	const static int SHAPES_KEY = 0;
	const static int SOLVER_KEY = 1;
private:
	unordered_map<int ,shared_ptr<Module>> mModules;
};