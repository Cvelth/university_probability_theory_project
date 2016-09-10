#pragma once
#include <map>
#include "AbstractTest.h"

using iPair = std::pair<uint64_t, uint16_t>;

class RangeTest : public AbstractTest
{
	std::map<uint64_t, uint16_t> m;
public:
	RangeTest();

	std::string test();
	std::string test(size_t size);

	~RangeTest();
};

