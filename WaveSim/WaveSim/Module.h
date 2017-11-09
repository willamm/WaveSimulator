#pragma once

class Module
{
public:
	virtual ~Module() = default;

	virtual inline int GetKey() const = 0;
};