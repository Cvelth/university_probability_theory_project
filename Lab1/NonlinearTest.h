#pragma once
#include "AbstractTest.h"
#include <map>

using bPair = std::pair<uint64_t, bool>;

class NonlinearTest : public AbstractTest
{
	std::map<uint64_t, bool> m;
public:
	NonlinearTest();

	std::string test(size_t t = 4);

	bool test(size_t n,int i);

	~NonlinearTest();
};

