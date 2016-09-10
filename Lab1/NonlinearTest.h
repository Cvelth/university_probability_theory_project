#pragma once
#include "AbstractTest.h"
#include <map>

using iPair = std::pair<uint64_t, uint16_t>;

class NonlinearTest : public AbstractTest
{
	std::map<uint64_t, bool> m;
public:
	NonlinearTest();

	std::string test();

	bool test(size_t n);

	~NonlinearTest();
};

