#pragma once
#include <set>

class Polynomial
{
	std::set<size_t> ones;

public:

	Polynomial() {	}

	Polynomial(std::initializer_list<size_t> ones) : ones(ones)	{	}

	//test func
	Polynomial* generate(size_t size, size_t capacity = 2)
	{
		ones.insert(0);
		for (int i = 1; i < size & ones.size() < capacity; i++)
			if (size % i != 0)
				ones.insert(i);
		ones.insert(size);
		return this;
	}

	~Polynomial() {	}
};

