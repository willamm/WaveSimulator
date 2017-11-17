#include "DatabaseRef.h"

using namespace std;

/**
 *	Constructor for the singleton class that holds multplie data modules.
*/
DatabaseRef::DatabaseRef()
	: mModules(unordered_map<int, shared_ptr<Module>>())
{
	mModules[DatabaseRef::SHAPES_KEY] = dynamic_pointer_cast<Module>(make_shared<ShapesModule>());
	mModules[DatabaseRef::SOLVER_KEY] = dynamic_pointer_cast<Module>(make_shared<SolverModule>());
}

/**
 *	GetModule(const int key)
 *		key: The integer key of a module
 *
 *	Retrieves a module based from the hash map using the key.
 *
 *	Returns a shared pointer to the module.
*/
shared_ptr<Module> DatabaseRef::GetModule(const int key) const
{
	return mModules.at(key);
}

const unordered_map<int, shared_ptr<Module>>& DatabaseRef::GetMap() const
{
	return mModules;
}
