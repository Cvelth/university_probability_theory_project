#include "Data.hpp"
#include <sstream>
#include <cfloat>

Data::Data() {
	d = new std::multiset<float>();
}

Data::Data(std::string input) : Data() {
	readString(input);
}

void Data::readString(std::string input) {
	std::istringstream s(input);
	float t;
	while (s >> t)
		d->insert(t);
}

std::vector<float> Data::divide(int i)
{
	return divide(i, min(), max());
}

std::vector<float> Data::divide(int i, float l, float r)
{
	std::vector<float> rs;
	rs.resize(i);
	float step = (r - l) / i;
	for (float f : *d)
		rs[((f - l) / step == 0 ? 1 : (f - l) / step) - 1]++;
	return rs;
}

float Data::min() {
	float r = FLT_MAX;
	for (float t : *d)
		if (r > t)
			r = t;
	return r;
}

float Data::max() {
	float r = -FLT_MAX;
	for (float t : *d)
		if (r < t)
			r = t;
	return r;
}

float Data::m() {
	float r = 0;
	for (float t : *d)
		r += t;
	return r / d->size();
}

float Data::s() {
	int x = m();
	float r = 0;
	for (float t : *d)
		r += (t - x) * (t - x);
	return sqrtf(r / d->size());
}