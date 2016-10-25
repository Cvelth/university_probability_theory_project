#pragma once
#include "Pair.hpp"
#include <random>

class CustomLawGenerator {
	const float STEP = 0.001;
	std::mt19937_64 m_g;
	std::uniform_real_distribution<float> m_d;
protected:
	template <class Func>
	float integrate(Func f) {
		float r = m_d(m_g), R = 0.f, x = 0.f;
		while (R < r)
			R += f(x += STEP) * STEP;
		return R > 1 ? 1 : R;
	}
	template <class Func>
	float integrate(Func f, float x0) {
		float left = -sqrtf(1 - (2 * x0 - 1)*(2 * x0 - 1)) / 2 + 0.5f;
		float right = sqrtf(1 - (2 * x0 - 1)*(2 * x0 - 1)) / 2 + 0.5f;
		float step = f(x0) * STEP;
		float r = m_d(m_g), R = 0.f, x = left;
		while (R < r) {
			R += step; x += STEP;
		}
		return x;
	}
public:
	CustomLawGenerator() {
		m_g = std::mt19937_64(std::random_device()());
		m_d = std::uniform_real_distribution<float>(0.f, 1.f);	
	}
	template <class LawFuncX, class LawFuncY>
	pair<float, float> operator()(LawFuncX& f_x, LawFuncY& f_y) {
		float x = integrate(f_x);
		float y = integrate(f_y, x);
		return pair<float, float>(x, y);
	}
};