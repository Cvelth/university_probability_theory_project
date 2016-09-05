#pragma once
#include "AbstractGenerator.h"
#include "Polynomial.h"
#include "Register.h"

class LFSR_superposed :	public virtual AbstractGenerator
{
	Polynomial poly;
	Register reg;

protected:
	void setRandom(AbstractGenerator* gen);

public:
	LFSR_superposed(size_t size);

	~LFSR_superposed();
};

