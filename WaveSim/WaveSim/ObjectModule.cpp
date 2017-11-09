#include "ObjectModule.h"

ObjectModule::ObjectModule()
	: mShapes(std::make_unique<std::vector<std::unique_ptr<LShape<double>>>>(new std::vector<std::unique_ptr<LShape<double>>>))
{
}

bool ObjectModule::AddRect(const int x, const int y, const int w, const int h, const double vel)
{
	int initSize = mShapes->size();

	std::unique_ptr<LRect<double>> tmp = std::make_unique<LRect<double>>(new LRect<double>(x, y, w, h, vel));
	mShapes->push_back(std::move(tmp));

	int postSize = mShapes->size();
	return postSize > initSize;
}

bool ObjectModule::AddCircle(const int x, const int y, const int r, const int vel)
{
	int initSize = mShapes->size();

	std::unique_ptr<LCircle<double>> tmp = std::make_unique<LCircle<double>>(new LCircle<double>(x, y, r, vel));
	mShapes->push_back(std::move(tmp));

	int postSize = mShapes->size();
	return false;
}

std::unique_ptr<std::vector<std::vector<LShape<double>>>> ObjectModule::GetShapes() const
{
	return std::unique_ptr<std::vector<std::vector<LShape<double>>>>();
}

bool ObjectModule::ClearAllObjects()
{
	mShapes->clear();
	return mShapes->empty();
}
