#pragma once
#include "Register.h"

class LFSR_spreaded : public AbstractGenerator
{
	Polynomial poly;
	Register reg;

public:
	LFSR_spreaded(size_t size);

	uint8_t getByte();
	Bit getBit();
	Bit step();

	~LFSR_spreaded();
};

