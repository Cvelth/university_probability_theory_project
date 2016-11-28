#pragma once
#include <Data.hpp>

const float PI = 3.14159265358979;

class Decider {
protected:
	static float normal(const float x, const float m, const float s) {
		return 1.f / sqrtf(2 * PI*s*s)*expf(-(x - m)*(x - m) / 2 / s / s);
	}
public:
	static float criticalY(Data d1, Data d2, float c1, float c2) {
		float m1 = d1.m(), m2 = d2.m();
		float s1 = d1.s(), s2 = d2.s();

		return (s1*s1*s2*s2 * logf(c1*s1 / c2 / s2) * 2 - m2*m2*s1*s1 + m1*m2*s2*s2) /
			(s1*s1*(-m2 * 2 + 1) - s2*s2*(m1 * 2 + 1));
	}

	static Flags criticalY_b(Data d1, Data d2, float c1, float c2) {
		Flags res;
		const int STEPS = 100;
		float mn = (d1.min() < d2.min()) ? d1.min() : d2.min();
		float mx = (d1.max() > d2.max()) ? d1.max() : d2.max();
		std::vector<float> v1 = d1.divide(STEPS, mn, mx),
			v2 = d2.divide(STEPS, mn, mx);
		for (int i = 0; i < STEPS; i++)
			if (v1[i] * c1 == v2[i] * c2)
				res.push_back(flag::e);
			else if (v1[i]*c1 > v2[i]*c2)
				res.push_back(flag::f);
			else
				res.push_back(flag::s);
		return res;
	}

	static Flags criticalY_bs(Data d1, Data d2, float c1, float c2) {
		Flags res;
		const int STEPS = 100;
		float m1 = d1.m(), m2 = d2.m();
		float s1 = d1.s(), s2 = d2.s();
		float mn = (d1.min() < d2.min()) ? d1.min() : d2.min();
		float mx = (d1.max() > d2.max()) ? d1.max() : d2.max();
		float step = (mx - mn) / STEPS;

		for (int i = 0; i < STEPS; i++) {
			float n1 = normal(mn + i*step, m1, s1) * c1;
			float n2 = normal(mn + i*step, m2, s2) * c2;

			if (n1 == n2)
				res.push_back(flag::e);
			else if (n1 > n2)
				res.push_back(flag::f);
			else
				res.push_back(flag::s);
		}
		return res;
	}
};