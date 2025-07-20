#include "vec3.h"
#include <cmath>
#include <iostream>
#include <cassert>

namespace Renderer {
	Vec::Vec() {
		_coordinates[0] = 0;
		_coordinates[1] = 0;
		_coordinates[2] = 0;
	}

	Vec::Vec(double x, double y, double z) {
		_coordinates[0] = x;
		_coordinates[1] = y;
		_coordinates[2] = z;
	}

	double Vec::operator[](int i) {
		return _coordinates[i];
	};

	double Vec::length() {
		return sqrt(_coordinates[0]* _coordinates[0] + _coordinates[1] * _coordinates[1] + _coordinates[2] * _coordinates[2]);
	}

	Vec Vec::operator+(Vec other) {
		Vec result(_coordinates[0] + other._coordinates[0], _coordinates[1] + other._coordinates[1], _coordinates[2] + other._coordinates[2]);
		return result;
	}

	Vec Vec::operator-() {
		Vec result(-_coordinates[0], -_coordinates[1], -_coordinates[2]);
		return result;
	}

	Vec Vec::operator*(double i) {
		Vec result(i*_coordinates[0], i*_coordinates[1], i*_coordinates[2]);
		return result;
	}

	double Vec::dot(Vec other) {
		double result = 0;
		for (int i = 0; i < 3; i++) {
			result += _coordinates[0] * other._coordinates[0];
		}
		return result;
	}

	Vec Vec::cross(Vec other) {
		double i = _coordinates[1] * other._coordinates[2] - _coordinates[2] * other._coordinates[1];
		double j = _coordinates[2] * other._coordinates[0] - _coordinates[0] * other._coordinates[2];
		double k = _coordinates[0] * other._coordinates[1] - _coordinates[1] * other._coordinates[0];
		Vec result(i, j, k);
		return result;
	}

	Vec Vec::norm() {
		double module = Vec::length();
		if (abs(module) < 1e-4) {
			assert(0);
		}
		return (*this) * (1 / module);
	}

	void Vec::print() {
		std::cout << _coordinates[0] << " -> " << _coordinates[1] << " -> " << _coordinates[2] << std::endl;
	}

	void Vec::vec_Test() {
		Vec y(4, 5, 6), x(1, 2, 3);
		x.print(); y.print();
		Vec i = x + y, j = x * 3.0, k = x.cross(y);
		double dotResult = x.dot(y);
		std::cout << "Sum: "; i.print();
		std::cout << "Multiplication: "; j.print();
		std::cout << "Cross x and y multiplication: "; k.print();
		x.print(); y.print();
		std::cout << "Dot multiplication: " << dotResult << std::endl;
	}

}