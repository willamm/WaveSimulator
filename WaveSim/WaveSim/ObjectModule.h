#pragma once
#include <memory>
#include <vector>

#include "LCircle.h"
#include "LShape.h"
#include "LRect.h"
#include "Module.h"

class ObjectModule final : Module
{
public:
	ObjectModule();
	~ObjectModule() = default;
	
	inline int GetKey() const
	{
		return KEY;
	}

	inline bool matchKey(const int key) const
	{
		return key == KEY;
	}

	bool AddRect(const int x, const int y, const int w, const int h, const double vel);
	bool AddCircle(const int x, const int y, const int r, const int vel);

	std::unique_ptr<std::vector<std::vector<LShape<double>>>> GetShapes() const;

	bool ClearAllObjects();

private:
	const static int KEY = 0xf9507d36d9f7d655;

	std::unique_ptr<std::vector<std::unique_ptr<LShape<double>>>> mShapes;
};