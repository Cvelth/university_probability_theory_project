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
	virtual uint64_t get() abstract;

	virtual ~AbstractGenerator()
	{
	}
};

