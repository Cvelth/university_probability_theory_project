#pragma once
#include <deque>

class Register :
	public std::deque<size_t>
{
public:
	Register();

	~Register();
};

