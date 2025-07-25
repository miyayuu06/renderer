#include "ray.h"

namespace Renderer {
	Ray::Ray(const Vec3& point, const Vec3& dir) {
		_origin = point;
		_direction = dir;
	}

	const Vec3 Ray::at(double t) {
		return _origin + (_direction * t);
	}

	const Vec3 Ray::origin() {
		return _origin;
	}

	const Vec3 Ray::dir() {
		return _direction;
	}

}