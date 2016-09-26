#pragma once
#include "AbstractGenerator.hpp"
#include <random>

using mt19937_64_float = std::mt19937_64 /*std::mersenne_twister_engine<float,
	64, 312, 156, 31, 0xb5026f5aa96619e9ULL, 29, 0x5555555555555555ULL, 17,
	0x71d67fffeda60000ULL, 37, 0xfff7eee000000000ULL, 43, 6364136223846793005ULL>*/;

class BuiltInGenerator : public AbstractGenerator
{
	mt19937_64_float *gen;
	std::normal_distribution<float> *d;

public:
	BuiltInGenerator(float m, float s)
	{
		gen = new mt19937_64_float(std::random_device()());
		d = new std::normal_distribution<float>(m, s);
	}
	float operator()()
	{
		return (*d)(*gen);
	}
};