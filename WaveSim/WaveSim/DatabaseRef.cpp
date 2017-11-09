#include "DatabaseRef.h"

DatabaseRef::DatabaseRef()
	: mModules(std::make_unique<std::unordered_map<int ,std::shared_ptr<Module>>>(new std::unordered_map<int, std::shared_ptr<Module>>))
{
}

std::shared_ptr<Module> DatabaseRef::GetModule(const int key) const
{
	return mModules->at(key);
}
