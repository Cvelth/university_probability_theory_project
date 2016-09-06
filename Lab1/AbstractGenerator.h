#pragma once
#include <cstdint>

class AbstractGenerator
{
public:

	AbstractGenerator()
	{
	}

	virtual uint8_t getByte() = 0;

	uint8_t operator()() //Register.cpp. Line 10.
	{
		return getByte();
	}

	virtual ~AbstractGenerator()
	{
	}
};

