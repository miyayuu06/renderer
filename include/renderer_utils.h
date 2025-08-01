#pragma once
#include <cmath>
#include <random>

inline double randomRealNumber(double minimum, double maximum) {
	double difference = maximum - minimum;
	return minimum + difference * (rand() / (RAND_MAX + 1.0));
}