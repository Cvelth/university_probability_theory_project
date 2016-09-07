#include "LFSR_spreaded.h"
#include "cGenerator.h"

LFSR_spreaded::LFSR_spreaded(size_t size, AbstractGenerator* gen)
{
	poly.generate(size);
	reg.resize(size);
	reg.setRandom(gen);
}

uint8_t LFSR_spreaded::getByte()
{
	uint8_t ret;
	for (int i = 0; i < 8; i++)
		ret ^= step() << i;
	return ret;
}

Bit LFSR_spreaded::getBit()
{
	return step();
}

uint64_t LFSR_spreaded::get()
{
	uint64_t ret;
	for (int i = 0; i < 64; i++)
		ret ^= step() << i;
	return ret;
}

Bit LFSR_spreaded::step()
{
	return reg << poly;
}

LFSR_spreaded::~LFSR_spreaded()
{
}