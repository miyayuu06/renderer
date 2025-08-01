#include "ray.h"

namespace Renderer {
	Ray::Ray() {}

	Ray::Ray(const Vec3& point, const Vec3& dir) : _origin(point), _direction(dir) {
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

}