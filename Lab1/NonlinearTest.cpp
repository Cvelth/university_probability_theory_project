#include "NonlinearTest.h"

NonlinearTest::NonlinearTest()
{
}

std::string NonlinearTest::test()
{
	uint64_t i = 1;
	while (!test(i++));
	std::ostringstream s;
	s << i;
	return s.str();
}

bool NonlinearTest::test(uint64_t n)
{
	for (uint64_t i = 0; i + n < v.size(); i++)
	{
		uint64_t sum = 0;
		for (uint64_t j = i; j < i + n; j++)
			sum ^= v[j] << j;
		m.insert(bPair(sum, v[i + n]));
		if (m[sum] == !v[i + n])
			return false;
	}
	return true;
}

NonlinearTest::~NonlinearTest()
{
}
