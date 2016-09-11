#include "FrequencyTest.h"

FrequencyTest::FrequencyTest()
{
}

std::string FrequencyTest::test(size_t t)
{
	double c = 0.0;
	for each (auto var in v)
		c += var;
	std::ostringstream s;
	s << c / v.size();
	return s.str();
}


FrequencyTest::~FrequencyTest()
{
}
