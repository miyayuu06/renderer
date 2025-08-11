#pragma once
#include <cmath>
#include <random>

inline double random() {
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

inline double randomRealNumber(double minimum, double maximum) {
	double difference = maximum - minimum;
	return minimum + difference * random();
}

inline double degreesToRadians(double deg) {
	const double PI = 3.1415926535897932384626433832795028841971;
	return (deg / 360) * 2 * PI;
}