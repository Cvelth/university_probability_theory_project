#pragma once
#include "AbstractGenerator.h"
#include <random>
#include <functional>

class CGenerator :	public virtual AbstractGenerator
{
	std::random_device generator;

public:

	CGenerator()
	{		
	}
	
	uint32_t getByte()
	{
		return generator();
	}

	~CGenerator()
	{
	}
};

