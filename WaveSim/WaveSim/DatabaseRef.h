#pragma once
#include <memory>
#include <unordered_map>

#include <Module.h>
#include <ShapesModule.h>

using namespace std;

class DatabaseRef final
{
public:
	DatabaseRef();
	~DatabaseRef() = default;

	shared_ptr<Module> GetModule(const int key) const;

	const static int SHAPES_KEY = 0xf9507d36d9f7d655;
private:
	unordered_map<int ,shared_ptr<Module>> mModules;
};
