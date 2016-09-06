#pragma once
#include "AbstractTest.h"
class DifferentialTest : public AbstractTest
{
public:
	DifferentialTest();

	long double test();

	~DifferentialTest();
};

