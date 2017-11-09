#pragma once
#include <memory>
#include <unordered_map>

#include <Module.h>
#include <ShapesModule.h>

class DatabaseRef final
{
public:
	DatabaseRef();
	~DatabaseRef() = default;

	std::shared_ptr<Module> GetModule(const int key) const;

	const static int SHAPES_KEY = 0xf9507d36d9f7d655;
private:
	std::unique_ptr<std::unordered_map<int ,std::shared_ptr<Module>>> mModules;
};
