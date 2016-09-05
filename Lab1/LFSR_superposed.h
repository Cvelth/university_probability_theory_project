#pragma once
#include "AbstractGenerator.h"
#include "Polynomial.h"
#include <deque>

class LFSR_superposed :
	public virtual AbstractGenerator<>
{
	Polynomial poly;
	std::deque<size_t> reg;

public:
	LFSR_superposed(size_t size);

	~LFSR_superposed();
};

