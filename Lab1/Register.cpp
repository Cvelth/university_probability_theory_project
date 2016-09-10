#include "Register.h"

Register::Register(size_t Size)
{
	resize(Size);
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
	Bit last = (data & (1 << size)) >> size, save = 0u;
	for (size_t i = 0; i < size; i++)
	{
		Bit t = bool(data & (1 << i));
		data ^= (save + (p.contains(i) ? last : 0u)) << i;
		save = t;
	}
	return save;
}

Register::~Register()
{
}
