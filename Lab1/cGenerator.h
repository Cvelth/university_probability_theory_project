#pragma once
#include "AbstractGenerator.h"
#include <random>
#include <chrono>

class CGenerator : public AbstractGenerator
{
	std::chrono::high_resolution_clock seed;
	std::mt19937_64 generator;

public:

	CGenerator()
	{		
		generator.seed(seed.now().time_since_epoch().count());
	}
	
	uint8_t getByte() 
	{
		return static_cast<uint8_t>(generator());
	}

	uint64_t get()
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

