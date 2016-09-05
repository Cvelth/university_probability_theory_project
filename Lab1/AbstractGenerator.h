#pragma once
#include <cstdint>

class AbstractGenerator
{
public:

	AbstractGenerator()
	{
	}

	virtual uint32_t getByte() = 0;

	virtual ~AbstractGenerator()
	{
	}
};

