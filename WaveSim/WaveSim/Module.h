#pragma once

class Module
{
public:
	virtual ~Module() = 0;

	virtual inline int GetKey() const = 0;
	virtual inline bool CheckKey(const int key) const = 0;
};