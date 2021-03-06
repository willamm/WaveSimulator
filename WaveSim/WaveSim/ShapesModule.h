#pragma once

#include <memory>
#include <vector>

#include "json.hpp"

#include "LCircle.h"
#include "LShape.h"
#include "LRect.h"
#include "Module.h"

using json = nlohmann::json;
using namespace std;

class ShapesModule final : public Module
{
public:
	ShapesModule();
	~ShapesModule() = default;

	const bool AddRect(const int x, const int y, const int w, const int h, const double vel);
	const bool AddCircle(const int x, const int y, const int r, const double vel);

	const vector<unique_ptr<LShape<double>>>& GetShapes() const;
	const bool ClearAllShapes();
	json GetJson();

private:
	vector<unique_ptr<LShape<double>>> mShapes;	/*! List of shapes for drawing. */
};
