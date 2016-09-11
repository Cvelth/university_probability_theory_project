#pragma once
#include "AbstractTest.h"
class FrequencyTest : public AbstractTest
{
public:
	FrequencyTest();

	std::string test(size_t t = 4);

	~FrequencyTest();
};

