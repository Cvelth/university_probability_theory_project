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

uint64_t NonlinearTest::test(size_t n)
{
	//To_develop!
	return 0ull;
}

NonlinearTest::~NonlinearTest()
{
}
