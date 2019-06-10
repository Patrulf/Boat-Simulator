#pragma once
#include <random>

//https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
static int Random(int p_from, int p_to)
{
	static std::random_device rd;
	static std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(p_from, p_to);

	return distr(eng);
}


