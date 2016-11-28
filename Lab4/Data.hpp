#pragma once
#include <set>
#include <vector>

enum flag {	f = -1, e = 0, s = +1 };
using Flags = std::vector<flag>;

class Data {
public:
	std::multiset<float>* d;

	Data();
	Data(std::string input);

	void readString(std::string input);
	std::vector<float> divide(int i);
	std::vector<float> divide(int i, float l, float r);
	float min();
	float max();
	float m();
	float s();

	std::multiset<float> operator*() { return *d; }
	std::multiset<float>* operator->() { return d; }
	auto operator[](float i) { return d->find(i); }
};