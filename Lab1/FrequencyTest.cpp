#include "FrequencyTest.h"



FrequencyTest::FrequencyTest()
{
}

long double FrequencyTest::test()
{
	long double c = 0.0l;
	for each (auto var in v)
		c += var;
	return c / v.size();
}


FrequencyTest::~FrequencyTest()
{
}
