#include "vec3.h"
#include "renderer_utils.h"

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
		return sqrt(lengthSquared());
	}

	double Vec3::lengthSquared() const {
		return _coordinates[0] * _coordinates[0] + _coordinates[1] * _coordinates[1] + _coordinates[2] * _coordinates[2];
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

	Vec3& Vec3::operator+=(const Vec3& other) {
		_coordinates[0] += other._coordinates[0];
		_coordinates[1] += other._coordinates[1]; 
		_coordinates[2] += other._coordinates[2];
		return *this;
	}

	Vec3 Vec3::operator*(double i) const {
		Vec3 result(i*_coordinates[0], i*_coordinates[1], i*_coordinates[2]);
		return result;
	}

	Vec3 Vec3::Vec3Mult(const Vec3& u, const Vec3& v) {
		return Vec3(u.x * v.x, u.y * v.y, u.z * v.z);
	}

	Vec3& Vec3::operator*=(double i) {
		_coordinates[0] *= i;
		_coordinates[1] *= i;
		_coordinates[2] *= i;
		return *this;
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
		if (abs(module) < 1e-100) {
			assert(0);
		}
		return *this / module;
	}

	Vec3 Vec3::random(double min, double max) {
		return Vec3(randomRealNumber(min, max), randomRealNumber(min, max), randomRealNumber(min, max));
	}

	Vec3 Vec3::random() {
		return Vec3(randomRealNumber(0.0, 1.0), randomRealNumber(0.0, 1.0), randomRealNumber(0.0, 1.0));
	}

	Vec3 Vec3::randomUnitVector() {
		while (true) {
			Vec3 result = random(-1.0, 1.0);
			double l = result.lengthSquared();
			if (1e-100 < l && l <= 1) {
				return result / sqrt(l);
			}
		}
	}

	Vec3 Vec3::randomUnitVectorInDisk() {
		while (true) {
			Vec3 p(randomRealNumber(-1, 1), randomRealNumber(-1, 1), 0.0);
			if (p.lengthSquared() < 1) {
				return p;
			}
		}
	}

	Vec3 Vec3::RUVHemisphereCorrector(const Vec3& surfaceNormal) {
		Vec3 RUV = randomUnitVector();
		if (RUV.dot(surfaceNormal) > 0.0) {
			return RUV;
		}
		return -RUV;
	}

	bool Vec3::nearZero() {
		return (std::abs(_coordinates[0]) <= 1e-8) && (std::abs(_coordinates[1]) <= 1e-8) && (std::abs(_coordinates[2]) <= 1e-8);
	}

	Vec3 Vec3::reflect(const Vec3& v, const Vec3& n) {
		return v - n * 2 * (v.dot(n));
	}

	Vec3 Vec3::refraction(const Vec3& r, const Vec3& n, double etaProportion) {
		double cosine = fmin((-r).dot(n), 1.0);
		Vec3 perp = (r + (n * cosine)) * etaProportion;
		double k = 1.0 - perp.lengthSquared();
		Vec3 parallel = (k < 0) ? Vec3(0.0) : n * -(sqrt(k));
		return perp + parallel;
	}

}