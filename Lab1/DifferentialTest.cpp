#include "DifferentialTest.h"



DifferentialTest::DifferentialTest()
{
}

long double DifferentialTest::test()
{
	long double c = 0.0l;
	for (size_t i = 2; i < v.size(); i++)
		c += v[i] ^ v[i - 1];
	return c / (v.size() - 1);
}


DifferentialTest::~DifferentialTest()
{
}
