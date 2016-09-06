#include "Register.h"

Register::Register()
{
}

void Register::setRandom(AbstractGenerator* gen)
{
	for (int i = 0; i < size(); i++)
		at(i) = (*gen)(); //Using operator()()
}

Bit Register::operator<<(const Polynomial & p)
{
	Bit last = at(size() - 1), save = last;
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
