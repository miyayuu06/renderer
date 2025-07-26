#include "vec3.h"
#include <cmath>
#include <iostream>
#include <cassert>

namespace Renderer {
	Vec3::Vec3() {
		_coordinates[0] = 0;
		_coordinates[1] = 0;
		_coordinates[2] = 0;
	}

	Vec3::Vec3(double x) {
		_coordinates[0] = x;
		_coordinates[1] = x;
		_coordinates[2] = x;
	}

	Vec3::Vec3(double x, double y, double z) {
		_coordinates[0] = x;
		_coordinates[1] = y;
		_coordinates[2] = z;
	}

	double Vec3::operator[](int i) const {
		return _coordinates[i];
	};

	double Vec3::length() const {
		return sqrt(_coordinates[0]* _coordinates[0] + _coordinates[1] * _coordinates[1] + _coordinates[2] * _coordinates[2]);
	}

	Vec3 Vec3::operator+(const Vec3& other) const {
		Vec3 result(_coordinates[0] + other._coordinates[0], _coordinates[1] + other._coordinates[1], _coordinates[2] + other._coordinates[2]);
		return result;
	}

	Vec3 Vec3::operator-() const {
		Vec3 result(-_coordinates[0], -_coordinates[1], -_coordinates[2]);
		return result;
	}

	Vec3 Vec3::operator-(const Vec3& other) const {
		Vec3 result(_coordinates[0] - other._coordinates[0], _coordinates[1] - other._coordinates[1], _coordinates[2] - other._coordinates[2]);
		return result;
	}

	Vec3 Vec3::operator*(double i) const {
		Vec3 result(i*_coordinates[0], i*_coordinates[1], i*_coordinates[2]);
		return result;
	}

	Vec3 Vec3::operator/(double i) const {
		return (*this) * (1 / i);
	}

	double Vec3::dot(const Vec3& other) const {
		double result = 0;
		for (int i = 0; i < 3; i++) {
			result += _coordinates[i] * other._coordinates[i];
		}
		return result;
	}

	Vec3 Vec3::cross(const Vec3& other) const {
		double i = _coordinates[1] * other._coordinates[2] - _coordinates[2] * other._coordinates[1];
		double j = _coordinates[2] * other._coordinates[0] - _coordinates[0] * other._coordinates[2];
		double k = _coordinates[0] * other._coordinates[1] - _coordinates[1] * other._coordinates[0];
		Vec3 result(i, j, k);
		return result;
	}

	Vec3 Vec3::norm() const {
		double module = Vec3::length();
		if (abs(module) < 1e-4) {
			assert(0);
		}
		return *this / module;
	}

	/*void Vec3::print() {
		std::cout << _coordinates[0] << " -> " << _coordinates[1] << " -> " << _coordinates[2] << std::endl;
	}

	void Vec3::Vec3_Test() {
		Vec3 y(4, 5, 6), x(1, 2, 3);
		x.print(); y.print();
		Vec3 i = x + y, j = x * 3.0, k = x.cross(y);
		double dotResult = x.dot(y);
		std::cout << "Sum: "; i.print();
		std::cout << "Multiplication: "; j.print();
		std::cout << "Cross x and y multiplication: "; k.print();
		x.print(); y.print();
		std::cout << "Dot multiplication: " << dotResult << std::endl;
	}*/

}