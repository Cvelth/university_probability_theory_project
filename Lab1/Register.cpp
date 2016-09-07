#include "Register.h"

Register::Register()
{
}

void Register::setRandom(AbstractGenerator* gen)
{
	for (int i = 0; i < size(); i++)
		at(i) = gen->getBit();
}

Bit Register::operator<<(const Polynomial & p)
{
	Bit last = at(size() - 1), save = 0u;
	for (size_t i = 0; i < size(); i++)
	{
		Bit t = at(i);
		at(i) = save + (p.contains(i) ? last : 0u);
		save = t;
	}
	return save;
}

Register::~Register()
{
}
