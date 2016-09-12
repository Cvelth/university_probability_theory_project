#include "NonlinearTest.h"

size_t NonlinearTest::start()
{
	size_t t = 1, max = 1;
	for (int i = 0; i < v.size() - 1; i++)
		if (v[i] == v[i + 1])
			max = ++t > max ? t : max;
		else
			t = 1;
	return max;
}

NonlinearTest::NonlinearTest()
{
}

std::string NonlinearTest::test(size_t t)
{
	uint64_t i = start();
	while (!test(i++, 0));
	std::ostringstream s;
	s << i;
	return s.str();
}

bool NonlinearTest::test(uint64_t n, int)
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
