#include "Importer.hpp"
#include <NormalGenerator.hpp>
#include <CustomLawGenerator.hpp>
#include <sstream>

std::string Importer::import1(float n, float s) {
	std::stringstream r;
	NormalGenerator g(0.f, s);
	for (int i = 0; i < n; i++)
		r << g() << '\t';
	return r.str();
}

std::string Importer::import2(float n, float m, float s) {
	std::stringstream r;
	NormalGenerator g(m,s);
	for (int i = 0; i < n; i++)
		r << g() << '\t';
	return r.str();
}
std::string Importer::import3(float n) {
	std::ostringstream r;
	CustomLawGenerator g;
	for (int i = 0; i < n / 2; i++) {
		pair<float, float> p = g([](float x) {
			return 4.f / PI*sqrtf(1.f - (2 * x - 1)*(2 * x - 1));
		}, [](float x) {
			return 1.f / sqrtf(1 - (2 * x - 1)*(2 * x - 1));
		});
		r << p.k() << '\t' << p.v() << '\t';
	}
	return r.str();
}