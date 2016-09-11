#include "RangeTest.h"

std::string RangeTest::binary(uint64_t a)
{
	std::string r = "";
	do
		r = ((a % 2) ? '1' : '0') + r;
	while (a /= 2);
	return r;
}

RangeTest::RangeTest()
{
}

std::string RangeTest::test(size_t size)
{
	std::ostringstream s;
	for (size_t i = 0; i+size < v.size(); i += size)
	{
		uint64_t sum = 0ull;
		for (size_t j = i; j < i + size; j++)
			sum ^= v[j] << (j - i);
		if (m.count(sum))
			m[sum]++;
		else
			m.insert(iPair(sum, 1u));
	}

	for each(auto var in m)
		s << binary(var.first) << '\t' << var.second << std::endl;
	return s.str();
}


RangeTest::~RangeTest()
{
}
