#pragma once
#include <string>
class Importer
{
public:
	static std::string import1(float n, float s);
	static std::string import2(float n, float m, float s);
	static std::string import3(float n);
private:
	Importer();
};