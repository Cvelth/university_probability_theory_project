#pragma once
#include <deque>
#include "AbstractGenerator.h"
#include "Polynomial.h"

class BoundsException {};

class Register 
{
	size_t size;
	uint64_t data;
	
public:
	Register(size_t size = 32);

	void resize(size_t size);
	void setRandom(AbstractGenerator* gen);
	Bit operator<<(const Polynomial& p);

	~Register();
};

