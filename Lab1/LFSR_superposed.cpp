#include "LFSR_superposed.h"

LFSR_superposed::LFSR_superposed(size_t size)
{
	reg.resize(size);
	poly.generate(size);
}

LFSR_superposed::~LFSR_superposed()
{
}
