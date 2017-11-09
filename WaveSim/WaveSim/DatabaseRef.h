#pragma once
#include <memory>
#include <unordered_map>

#include <Module.h>

class DatabaseRef final
{
public:
	DatabaseRef();
	~DatabaseRef() = default;

	std::shared_ptr<Module> GetModule(const int key) const;

private:
	std::unique_ptr<std::unordered_map<int ,std::shared_ptr<Module>>> mModules;
};
