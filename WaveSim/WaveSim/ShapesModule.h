#pragma once
#include <memory>
#include <vector>

#include "LCircle.h"
#include "LShape.h"
#include "LRect.h"
#include "Module.h"

class ShapesModule final : public Module
{
public:
	ShapesModule();
	~ShapesModule() = default;
	
	inline int GetKey() const
	{
		return KEY;
	}

	inline bool MatchKey(const int key) const
	{
		return key == KEY;
	}

	bool AddRect(const int x, const int y, const int w, const int h, const double vel);
	bool AddCircle(const int x, const int y, const int r, const int vel);

	std::vector<std::unique_ptr<LShape<double>>> GetShapes() const;

	bool ClearAllShapes();

private:
	const static int KEY = 0xf9507d36d9f7d655;

	std::shared_ptr<std::vector<std::unique_ptr<LShape<double>>>> mShapes;
};