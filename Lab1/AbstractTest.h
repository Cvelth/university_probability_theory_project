#pragma once
#include "Bit.h"
#include <fstream>
#include <vector>

class AbstractTest
{
protected:
	std::vector<Bit> v;
public:
	AbstractTest()
	{
	}

	void setSequence(std::ifstream f)
	{
		char c;
		while (f >> c)
			v.push_back(c == '1' ? true : false);
	}

	void setSequence(std::vector<Bit> d)
	{
		v = d;
	}

	virtual long double test() = 0;

	virtual ~AbstractTest()
	{
	}
};

