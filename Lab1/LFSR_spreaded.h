#pragma once
#include "Register.h"
#include "cGenerator.h"

class LFSR_spreaded : public AbstractGenerator
{
	Polynomial poly;
	Register reg;

public:
	LFSR_spreaded(size_t size, AbstractGenerator* gen = new CGenerator());

	uint8_t getByte();
	Bit getBit();
	uint64_t get();
	Bit step();

	~LFSR_spreaded();
};

