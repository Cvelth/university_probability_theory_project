#pragma once
#include <cstdint>
#include <deque>
#include <string>

class BoundsException {};

class BinaryNumber
{
	const size_t BITS_PER_NUMBER = 31;
	const uint64_t MAXIMUM_PER_NUMBER = pow(2, BITS_PER_NUMBER);
	std::deque<uint64_t> data;

protected:
	void add(uint64_t num);
	BinaryNumber complement(BinaryNumber b);
	std::string cutZeros(std::string s);

public:
	BinaryNumber();
	BinaryNumber(uint64_t num);
	BinaryNumber(std::initializer_list<uint64_t> list);

	BinaryNumber operator=(BinaryNumber n);
	BinaryNumber operator+(BinaryNumber n);

	bool operator[](size_t el);
	std::string print();

	~BinaryNumber();
};

