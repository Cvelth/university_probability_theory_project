#include "NonlinearTest.h"

NonlinearTest::NonlinearTest()
{
}

long double NonlinearTest::test()
{
	uint64_t i = 1;
	while (!test(i++));
	return static_cast<long double>(i);
}

uint64_t NonlinearTest::test(size_t n)
{
	//To_develop!
}

NonlinearTest::~NonlinearTest()
{
}
