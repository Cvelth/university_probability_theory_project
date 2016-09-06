#include "LFSR_spreaded.h"
#include "cGenerator.h"

LFSR_spreaded::LFSR_spreaded(size_t size)
{
	poly.generate(size);
	reg.resize(size);
	reg.setRandom(new CGenerator());
}

uint8_t LFSR_spreaded::getByte()
{
	return uint8_t();
}

Bit LFSR_spreaded::step()
{
	return reg << poly;
}

LFSR_spreaded::~LFSR_spreaded()
{
}