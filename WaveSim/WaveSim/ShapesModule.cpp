#include "ShapesModule.h"

ShapesModule::ShapesModule()
	: mShapes(std::make_shared<std::vector<std::unique_ptr<LShape<double>>>>())
{
}

bool ShapesModule::AddRect(const int x, const int y, const int w, const int h, const double vel)
{
	int initSize = mShapes->size();

	//std::unique_ptr<LRect<double>> tmp = std::make_unique<LRect<double>>(new LRect<double>(x, y, w, h, vel));
	mShapes->push_back(std::make_unique<LRect<double>>(x, y, w, h , vel));

	int postSize = mShapes->size();
	return postSize > initSize;
}

bool ShapesModule::AddCircle(const int x, const int y, const int r, const int vel)
{
	int initSize = mShapes->size();

	mShapes->push_back(std::make_unique<LCircle<double>>(x, y, r, vel));

	int postSize = mShapes->size();
	return false;
}

std::vector<std::unique_ptr<LShape<double>>> ShapesModule::GetShapes() const
{
	return std::vector<std::unique_ptr<LShape<double>>>();
}

bool ShapesModule::ClearAllShapes()
{
	mShapes->clear();
	return mShapes->empty();
}
