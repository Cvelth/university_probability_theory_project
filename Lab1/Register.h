#pragma once
#include <deque>
#include "AbstractGenerator.h"
#include "Polynomial.h"

class Register :
	public std::deque<Bit>
{
public:
	Register();

	void setRandom(AbstractGenerator* gen);
	Bit operator<<(const Polynomial& p);

	~Register();
};

