#include "sphere.h"
#include <cmath>

namespace Renderer {
	Sphere::Sphere(Vec center, double r) {
		sphereCenter = center;
		radius = r;
	}

	bool Sphere::hit(double tmin, double tmax, Ray& r, HitProperties& prop) {
		Vec centerDistance = sphereCenter + (-r.origin());
		double a = (r.dir()).dot(r.dir());
		double h = r.dir().dot(centerDistance);
		double c = (centerDistance.dot(centerDistance)) - (radius * radius);
		double discriminant = (h * h) - (a * c);

		if (discriminant < 0) {
			return false;
		}

		double collisionPoint = (h + sqrt(discriminant)) / a;
		if (tmin >= collisionPoint || tmax <= collisionPoint) {
			collisionPoint = (h - sqrt(discriminant)) / a;
				if (tmin >= collisionPoint || tmax <= collisionPoint) {
					return false;
				}
		}
		prop.tValue = collisionPoint;
		prop.intersectionPoint = r.at(collisionPoint);
		prop.normal = ((prop.intersectionPoint + -sphereCenter) * (1 / radius) + Vec(1.0, 1.0, 1.0))*0.5;

		return true;
	}

}