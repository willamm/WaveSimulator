#include "ShapesModule.h"

using namespace std;

ShapesModule::ShapesModule()
	: mShapesModule(vector<unique_ptr<LShape<double>>>())
{
}

const bool ShapesModule::AddRect(const int x, const int y, const int w, const int h, const double vel)
{
	int initSize = mShapesModule.size();
	mShapesModule.push_back(make_unique<LRect<double>>(x, y, w, h , vel));
	int postSize = mShapesModule.size();
	return postSize > initSize;
}

const bool ShapesModule::AddCircle(const int x, const int y, const int r, const int vel)
{
	int initSize = mShapesModule.size();
	mShapesModule.push_back(make_unique<LCircle<double>>(x, y, r, vel));
	int postSize = mShapesModule.size();
	return false;
}

const vector<unique_ptr<LShape<double>>>& ShapesModule::GetShapes() const
{
	return mShapesModule;
}

const bool ShapesModule::ClearAllShapes()
{
	mShapesModule.clear();
	return mShapesModule.empty();
}
