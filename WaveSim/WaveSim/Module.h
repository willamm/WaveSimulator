#pragma once

class Module
{
public:
	Module() = delete;
	virtual ~Module();

	inline int GetKey() { return KEY; }
	inline bool CheckKey(int key) { return key == KEY; }
protected:
	const static int KEY = 0;
};