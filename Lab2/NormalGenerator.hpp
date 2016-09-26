#pragma once
#include "AbstractGenerator.hpp"
#include <cmath>
#include <random>

#define C_PI       3.14159265358979323846

class NormalGenerator : public AbstractGenerator
{
	float m, s;
	std::mt19937_64 *gen;
	std::uniform_real_distribution<float> *d;
public:
	NormalGenerator(float m, float s) : m(m), s(s)
	{
		gen = new std::mt19937_64(std::random_device()());
		d = new std::uniform_real_distribution<float>(0.f,1.f);
	}

	float operator()()
	{
		return s * (sqrtf(-2 * logf( (*d)(*gen) )) *
					sinf(2 * C_PI * (*d)(*gen) )) + m;
	}
};