#include "BinaryNumber.h"

void BinaryNumber::add(uint64_t num)
{
	while (num >= MAXIMUM_PER_NUMBER) 
	{
		data.push_back(num % MAXIMUM_PER_NUMBER);
		num /= MAXIMUM_PER_NUMBER;
	}
	data.push_back(num);
}

BinaryNumber BinaryNumber::complement(BinaryNumber b)
{
	if (data.size() >= b.data.size())
		throw BoundsException();

	data.resize(b.data.size());

	return *this;
}

std::string BinaryNumber::cutZeros(std::string s)
{
	int i = 0;
	std::string res;
	while (s[i] != '1' & i < s.size()) i++;
	while (i < s.size()) res += s[i++];
	return res;
}

BinaryNumber::BinaryNumber() : data(0)
{
}

BinaryNumber::BinaryNumber(uint64_t num)
{
	if (num != 0)
		add(num);
}

BinaryNumber::BinaryNumber(std::initializer_list<uint64_t> list)
{
	uint64_t trans = 0;
	for each (auto var in list)
	{
		if ((var += trans) > MAXIMUM_PER_NUMBER)
		{
			data.push_back(var % MAXIMUM_PER_NUMBER);
			trans = var / MAXIMUM_PER_NUMBER;
		}
		else
		{
			data.push_back(var);
			trans = 0;
		}
	}
	if (trans != 0)
		add(trans);
}

BinaryNumber BinaryNumber::operator=(BinaryNumber n)
{
	data = n.data;
	return *this;
}

BinaryNumber BinaryNumber::operator+(BinaryNumber n)
{
	if (n.data.size() > data.size())
		complement(n);
	else
		n.complement(*this);

	uint64_t trans = 0;
	for (auto i1 = n.data.begin(), i2 = data.begin();
		 i1 != n.data.end() & i2 != data.end();
		 i1++, i2++)
	{
		*i1 += *i2 + trans;
		if (*i1 >= MAXIMUM_PER_NUMBER)
		{
			trans = *i1 / MAXIMUM_PER_NUMBER;
			*i1 %= MAXIMUM_PER_NUMBER;
		}
		else
			trans = 0;
	}
	if (trans != 0)
		n.add(trans);

	return n;
}

BinaryNumber BinaryNumber::operator&(BinaryNumber n)
{
	for (std::deque<uint64_t>::iterator i1 = n.data.begin(), i2 = data.begin();
		 i1 != n.data.end() & i2 != data.end(); i1++, i2++)
		*i1 &= *i2;
	return n;
}

BinaryNumber BinaryNumber::operator|(BinaryNumber n)
{
	for (std::deque<uint64_t>::iterator i1 = n.data.begin(), i2 = data.begin();
		 i1 != n.data.end() & i2 != data.end(); i1++, i2++)
		*i1 |= *i2;
		return n;
}

bool BinaryNumber::operator[](size_t el)
{
	size_t num = el / BITS_PER_NUMBER;
	el %= BITS_PER_NUMBER;
	if (num < data.size())
		return ((1 << el) & data[num]) >> el;
	else
		return 0;
}

std::string BinaryNumber::print()
{
	std::string s;
	for each (auto var in data)
		for (int i = 0; i < BITS_PER_NUMBER; i++)
			s = ((1 << i & var) >> i ? '1' : '0') + s;
	return cutZeros(s);
}

BinaryNumber::~BinaryNumber()
{
}
