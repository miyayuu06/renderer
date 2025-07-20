#include "ray.h"

namespace Renderer {
	Ray::Ray(Vec point, Vec dir) {
		_origin = point;
		_direction = dir;
	}

	Vec Ray::at(double t) {
		return _origin + _direction * t;
	}

	Vec Ray::dir() {
		return _direction;
	}

	Vec Ray::ray_color() {
		Vec unitVector = _direction.Vec::norm();
		double a = (unitVector._coordinates[1] + 1.0)*0.5;
		return (Vec(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec(1.0, 0.77, 1.0) * a);
	}

}