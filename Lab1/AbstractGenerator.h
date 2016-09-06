#pragma once
#include "Bit.h"
#include <cstdint>

class AbstractGenerator
{
public:

	AbstractGenerator()
	{
	}

	virtual uint8_t getByte() abstract;
	virtual Bit getBit() abstract;


	uint8_t operator()() //Register.cpp. Line 10.
	{
		return getByte();
	}

	virtual ~AbstractGenerator()
	{
	}
};

