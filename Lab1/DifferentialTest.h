#pragma once
#include "AbstractTest.h"
class DifferentialTest : public AbstractTest
{
public:
	DifferentialTest();

	std::string test(size_t t = 4);

	~DifferentialTest();
};

