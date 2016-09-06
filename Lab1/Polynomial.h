#pragma once
#include <set>
#include "Bit.h"

class Polynomial
{
	std::set<size_t> ones;
	size_t size;

public:

	Polynomial() : size(0) {	}

	Polynomial(std::initializer_list<size_t> data) : size(0)
	{	
		for each (auto var in data)
		{
			ones.insert(var);
			size = var > size ? var : size;
		}
	}

	//test func
	Polynomial* generate(size_t size, size_t capacity = 2)
	{
		this->size = size;
		ones.insert(0);
		for (int i = 1; i < size & ones.size() < capacity; i++)
			if (size % i != 0)
				ones.insert(i);
		ones.insert(size);
		return this;
	}
	
	bool contains(size_t p) const
	{
		return ones.find(p) != ones.end();
	}

	~Polynomial() {	}
};

