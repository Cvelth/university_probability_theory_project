#pragma once
#include "Bit.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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
			v.push_back(c == '1');
	}

	void setSequence(std::vector<Bit> d)
	{
		v = d;
	}

	virtual std::string test() = 0;

	virtual ~AbstractTest()
	{
	}
};

