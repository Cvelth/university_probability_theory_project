#pragma once
#include "AbstractTest.h"
#include <map>

class NonlinearTest : public AbstractTest
{
	std::map<uint64_t, bool> s;
public:
	NonlinearTest();

	long double test();

	uint64_t test(size_t n);

	~NonlinearTest();
};

