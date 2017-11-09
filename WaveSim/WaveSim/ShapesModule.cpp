#include "ShapesModule.h"

using namespace std;

ShapesModule::ShapesModule()
	: mShapes(vector<unique_ptr<LShape<double>>>())
{
}

const bool ShapesModule::AddRect(const int x, const int y, const int w, const int h, const double vel)
{
	int initSize = mShapes.size();
	mShapes.push_back(make_unique<LRect<double>>(x, y, w, h , vel));
	int postSize = mShapes.size();
	return postSize > initSize;
}

const bool ShapesModule::AddCircle(const int x, const int y, const int r, const int vel)
{
	int initSize = mShapes.size();
	mShapes.push_back(make_unique<LCircle<double>>(x, y, r, vel));
	int postSize = mShapes.size();
	return false;
}

const vector<unique_ptr<LShape<double>>>& ShapesModule::GetShapes() const
{
	return mShapes;
}

const bool ShapesModule::ClearAllShapes()
{
	mShapes.clear();
	return mShapes.empty();
}
