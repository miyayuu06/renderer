#include "ray.h"

namespace Renderer {
	Ray::Ray(Vec point, Vec dir) {
		_origin = point;
		_direction = dir;
	}

	Vec Ray::at(double t) {
		return _origin + _direction * t;
	}
}