#include "ray.h"

namespace Renderer {
	Ray::Ray() {}

	Ray::Ray(const Vec3& point, const Vec3& dir, double t) : _origin(point), _direction(dir), time(t) {
	}

	Ray::Ray(const Vec3& point, const Vec3& dir) : _origin(point), _direction(dir) {
		time = 0.0;
	}

	Vec3 Ray::at(double t) const {
		return _origin + (_direction * t);
	}

	Vec3 Ray::origin() const {
		return _origin;
	}

	Vec3 Ray::dir() const {
		return _direction;
	}

	double Ray::tm() const {
		return time;
	}

}