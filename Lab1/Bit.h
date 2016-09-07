#pragma once
#include <cstdint>
class Bit
{
	bool b;
public:

	Bit() : b(false)
	{
	}

	Bit(bool a) : b(a)
	{
	}

	Bit(uint8_t a)
	{
		b = (a > UINT8_MAX / 2) ? 1 : 0;
	}

	Bit(uint64_t a)
	{
		b = (a > UINT64_MAX / 2) ? 1 : 0;
	}

	Bit(unsigned int a) //16 bit one(I presume)
	{
		b = (a > UINT16_MAX / 2) ? 1 : 0;
	}

	Bit operator+(Bit a)
	{
		return a.b != b;
	}

	operator bool()
	{
		return b;
	}

	~Bit()
	{
	}
};

