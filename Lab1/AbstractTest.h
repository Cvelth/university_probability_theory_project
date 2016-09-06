#pragma once
#include <fstream>
#include <vector>

class AbstractTest
{
protected:
	std::vector<bool> v;
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

	virtual long double test() = 0;

	virtual ~AbstractTest()
	{
	}
};

