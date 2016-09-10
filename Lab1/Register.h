#pragma once
#include <set>
#include "AbstractGenerator.h"

class Register;
class BoundsException {};

class Polynomial
{
	std::set<size_t> ones;
	size_t size;

public:

	Polynomial();
	Polynomial(std::initializer_list<size_t> data);

	Polynomial * generate(size_t size, size_t capacity = 2);
	bool contains(size_t p) const;
	Register getOnes() const;

	~Polynomial();
};


class Register 
{
	size_t size;
	uint64_t data;
	
protected:
	Bit last();

public:
	Register(size_t size = 32);
	Register(size_t size, uint64_t data);

	void resize(size_t size);
	void setRandom(AbstractGenerator* gen);

	Bit operator<<(const Polynomial& p);
	Bit operator[](size_t i);

	operator uint64_t()
	{
		return data;
	}

	~Register();
};

