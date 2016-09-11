#pragma once
#include <map>
#include "AbstractTest.h"

using iPair = std::pair<uint64_t, uint16_t>;

class RangeTest : public AbstractTest
{
	std::map<uint64_t, uint16_t> m;

protected:
	std::string binary(uint64_t a);

public:
	RangeTest();

	std::string test(size_t t = 4);

	~RangeTest();
};

