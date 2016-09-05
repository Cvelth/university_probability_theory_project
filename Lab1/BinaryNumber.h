#pragma once
#include <cstdint>
#include <deque>
#include <string>

class BoundsException {};

class BinaryNumber
{
	const size_t BITS_PER_NUMBER = 4;
	std::deque<uint64_t> data;

protected:
	BinaryNumber complement(BinaryNumber b);
	std::string cutZeros(std::string s);
	//std::string invert(std::string s);

public:
	BinaryNumber();
	BinaryNumber(uint64_t num);
	BinaryNumber(std::initializer_list<uint64_t> list);

	BinaryNumber operator+(BinaryNumber n);

	bool operator[](size_t el);
	std::string print();

	~BinaryNumber();
};

