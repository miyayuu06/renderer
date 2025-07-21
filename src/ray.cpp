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

	Vec Ray::ray_color(Vec sphereCenter, double radius) {
		if (hitSphere(sphereCenter, radius)) {
			return Vec(1.0, 0, 0);
		}

		Vec unitVector = _direction.Vec::norm();
		double a = (unitVector.y + 1.0)*0.5;
		return (Vec(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec(0.5, 0.77, 1.0) * a);
	}

	bool Ray::hitSphere(Vec sphereCenter, double radius) {
		Vec centerDistance = sphereCenter + (-_origin);
		double a = _direction.dot(_direction);
		double b = _direction.dot(centerDistance) * -2.0;
		double c = (centerDistance.dot(centerDistance)) - (radius * radius);
		double discriminant = (b * b) - (4 * a * c);
		return (discriminant >= 0);
	}

}