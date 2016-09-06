#pragma once
#include "AbstractGenerator.h"
#include "Polynomial.h"
#include "Register.h"

class LFSR_spreaded : public virtual AbstractGenerator
{
	Polynomial poly;
	Register reg;

public:
	LFSR_spreaded(size_t size);

	uint8_t getByte();
	Bit step();

	~LFSR_spreaded();
};

