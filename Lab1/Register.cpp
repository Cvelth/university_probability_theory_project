#include "Register.h"

Polynomial::Polynomial() : size(0) {	}

Polynomial::Polynomial(std::initializer_list<size_t> data) : size(0)
{
	for each (auto var in data)
	{
		ones.insert(var);
		size = var > size ? var : size;
	}
}

//test func
Polynomial* Polynomial::generate(size_t size, size_t capacity)
{
	this->size = size;
	ones.insert(0);
	for (int i = 1; i < size & ones.size() < capacity; i++)
		if (size % i != 0)
			ones.insert(i-1);
	ones.insert(size-1);
	return this;
}

bool Polynomial::contains(size_t p) const
{
	return ones.find(p) != ones.end();
}

Register Polynomial::getOnes() const
{
	uint64_t ret = 0ull;
	for each(size_t var in ones)
		ret ^= 1 << var;
	return Register(size, ret);
}

Polynomial::~Polynomial() {	}

//REGISTER!!!

Bit Register::last()
{
	return operator[](size);
}

Register::Register(size_t Size)
{
	resize(Size);
}

Register::Register(size_t Size, uint64_t Data)
{
	resize(Size);
	data = Data;
}

void Register::resize(size_t Size)
{
	if (Size >= 64 || Size <= 0)
		throw BoundsException();
	size = Size;
	data = 0ull;
}

void Register::setRandom(AbstractGenerator* gen)
{
	for (int i = 0; i < size; i++)
		data ^= gen->getBit() << i;
}

Bit Register::operator<<(const Polynomial & p)
{
	data <<= 1;
	if (operator[](size)) data ^= (((p.getOnes() ^ (1 << (size - 1))) ^ 1) << 1) ^ 1;
	return operator[](size);
}

Bit Register::operator[](size_t i)
{
	return bool((data & (1 << i)) >> i);
}

Register::~Register()
{
}
