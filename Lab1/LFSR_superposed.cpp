#include "LFSR_superposed.h"

void LFSR_superposed::setRandom(AbstractGenerator * gen)
{

}

LFSR_superposed::LFSR_superposed(size_t size)
{
	poly.generate(size);
	reg.resize(size);
}

LFSR_superposed::~LFSR_superposed()
{
}
