#include "TableGenerator.h"

void TableGenerator::generate(size_t RegNum, size_t RegSize)
{
	for (int i = 0; i < RegNum; i++)
		gens.push_back(new LFSR_spreaded(RegSize));
}

TableGenerator::TableGenerator(size_t RegNum, size_t RegSize, Table* tbl) : RegNum(RegNum), RegSize(RegSize), tbl(tbl)
{
	generate(RegNum, RegSize);
}

TableGenerator::TableGenerator(size_t RegNum, size_t RegSize, AbstractGenerator* gen) : RegNum(RegNum), RegSize(RegSize)
{
	generate(RegNum, RegSize);
	newTable(gen);
}

void TableGenerator::newTable(AbstractGenerator * gen)
{
	tbl = new Table();
	tbl->generate(1ull << RegNum, gen);
}

Bit TableGenerator::getBit()
{
	uint64_t code = 0ull;
	for (int i = 0; i < RegNum; i++)
		code ^= (gens[i]->getBit() == Bit(true) ? 1ull : 0ull) << i;
	return (*tbl)[code];
}

uint8_t TableGenerator::getByte()
{
	uint8_t ret;
	for (int i = 0; i < 8; i++)
		ret ^= getBit() << i;
	return ret;
}

uint64_t TableGenerator::get()
{
	uint64_t ret;
	for (int i = 0; i < 64; i++)
		ret ^= getBit() << i;
	return ret;
}


TableGenerator::~TableGenerator()
{
	delete tbl;
}
