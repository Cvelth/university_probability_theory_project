#include "DifferentialTest.h"



DifferentialTest::DifferentialTest()
{
}

std::string DifferentialTest::test(size_t t)
{
	long double c = 0.0l;
	for (size_t i = 2; i < v.size(); i++)
		c += v[i] ^ v[i - 1];
	std::ostringstream s;
	s << c / (v.size() - 1);
	return s.str();
}


DifferentialTest::~DifferentialTest()
{
}
