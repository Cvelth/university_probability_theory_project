#pragma once
#include "AbstractGenerator.h"
#include <vector>
#include <fstream>

class Table
{
	std::vector<Bit> items;
public:

	Table()
	{
	}

	void generate(size_t size, AbstractGenerator* gen)
	{
		for (int i = 0; i < size; i++)
			items.push_back(gen->getBit());
	}

	Bit get(uint64_t index)
	{
		return items[index];
	}

	Bit operator[](uint64_t index)
	{
		return get(index);
	}

	void save(std::ofstream f = std::ofstream("Table.txt"))
	{
		f << items.size() << std::endl;
		for each (auto var in items)
			f << var;
		f.close();
	}

	Table* load(std::ifstream f = std::ifstream("Table.txt"))
	{
		size_t n, t;
		f >> n;
		items.clear();
		for (int i = 0; i < n; i++)
		{
			f >> t;
			items.push_back(t);
		}
		f.close();
		return this;
	}

	~Table()
	{
	}
};

