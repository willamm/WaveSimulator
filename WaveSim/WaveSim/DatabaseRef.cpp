#include "DatabaseRef.h"

using namespace std;

DatabaseRef::DatabaseRef()
	: mModules(unordered_map<int, shared_ptr<Module>>())
{
	mModules[DatabaseRef::SHAPES_KEY] = dynamic_pointer_cast<Module>(make_shared<ShapesModule>());
	mModules[DatabaseRef::SOLVER_KEY] = dynamic_pointer_cast<Module>(make_shared<SolverModule>());
}

shared_ptr<Module> DatabaseRef::GetModule(const int key) const
{
	return mModules.at(key);
}

const unordered_map<int, shared_ptr<Module>>& DatabaseRef::GetMap() const
{
	return mModules;
}
