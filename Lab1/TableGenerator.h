#pragma once
#include "cGenerator.h"
#include "LFSR_spreaded.h"
#include "Table.h"

class TableGenerator : public AbstractGenerator
{
	size_t RegNum, RegSize;
	std::vector<LFSR_spreaded*> gens;
	Table* tbl;
protected:
	void generate(size_t RegNum, size_t RegSize);

public:
	TableGenerator(size_t RegNum, size_t RegSize, Table* tbl);
	TableGenerator(size_t RegNum, size_t RegSize, AbstractGenerator* gen = new CGenerator());

	void newTable(AbstractGenerator* gen);

	Bit getBit();
	uint8_t getByte();
	uint64_t get();

	~TableGenerator();
};

