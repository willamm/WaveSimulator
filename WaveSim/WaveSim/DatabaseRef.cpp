#include "DatabaseRef.h"

DatabaseRef::DatabaseRef()
	: mModules(std::make_unique<std::unordered_map<int ,std::shared_ptr<Module>>>())
{
	std::shared_ptr<Module> shapes = std::dynamic_pointer_cast<Module>(std::make_shared<ShapesModule>());
	(*mModules)[shapes->GetKey()] = shapes;
}

std::shared_ptr<Module> DatabaseRef::GetModule(const int key) const
{
	return (*mModules)[key];
}
