#pragma once
#include <vector>

const float PI = 3.141592653589793;

template <typename KEY_T, typename VALUE_T>
class pair {
	KEY_T m_key;
	VALUE_T m_value;
public:
	explicit pair(const KEY_T& key, const VALUE_T& value) : m_key(key), m_value(value) {};
	explicit pair(KEY_T&& key, VALUE_T&& value) : m_key(key), m_value(value) {};
	KEY_T k() { return m_key; }
	VALUE_T v() { return m_value; }
	void k(const KEY_T& key) { m_key = key; }
	void k(KEY_T&& key) { m_key = key; }
	void v(const VALUE_T& value) { m_value = value; }
	void v(VALUE_T&& value) { m_value = value; }
};

class Data {
public:
	std::vector<pair<float, float>>* v;
	float m_x, m_y;
	float D_x, D_y;
	float S_x, S_y;
	float cov, Ro;

	Data() { 
		v = new std::vector<pair<float, float>>(); 
		m_x = m_y = D_x = D_y = S_x = S_y = cov = Ro = 0.f; 
	}

	Data& S() {
		S_x = sqrtf(D_x);
		S_y = sqrtf(D_y);
		return *this;
	}
	Data& R() {
		S();
		Ro = cov / S_x / S_y;
		return *this;
	}

	std::vector<pair<float, float>> operator*() { return *v; }
	std::vector<pair<float, float>>* operator->() { return v; }
	pair<float, float>& operator[](int i) { return (*v)[i]; }
};