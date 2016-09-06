#pragma once
#include "AbstractGenerator.h"
#include <random>
#include <functional>

class CGenerator : public AbstractGenerator
{
	std::random_device generator;

public:

	CGenerator()
	{		
	}
	
	uint8_t getByte() 
	{
		return generator();
	}
	Bit getBit() 
	{
		return Bit(generator());
	}

	~CGenerator()
	{
	}
};

