#include "DatabaseRef.h"

using namespace std;

DatabaseRef::DatabaseRef()
	: mModules(unordered_map<int ,shared_ptr<Module>>())
{
	shared_ptr<Module> shapes = dynamic_pointer_cast<Module>(make_shared<ShapesModule>());
	mModules[DatabaseRef::SHAPES_KEY] = shapes;
}

shared_ptr<Module> DatabaseRef::GetModule(const int key) const
{
	return mModules.at(key);
}
