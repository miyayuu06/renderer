#include "sphere.h"
#include <cmath>

namespace Renderer {
	Sphere::Sphere(const Vec3 center, double r) {
		sphereCenter = center;
		radius = r;
	}

	bool Sphere::hit(const Interval& interval, const Ray& r, HitProperties& prop) const {
		Vec3 centerDistance = sphereCenter - r.origin();
		double a = (r.dir()).dot(r.dir());
		double h = r.dir().dot(centerDistance);
		double c = (centerDistance.dot(centerDistance)) - (radius * radius);
		double discriminant = (h * h) - (a * c);

		if (discriminant < 0) {
			return false;
		}

		double collisionPoint = (h - sqrt(discriminant)) / a;
		if (!interval.belongs(collisionPoint)) {
			collisionPoint = (h + sqrt(discriminant)) / a;
				if (!interval.belongs(collisionPoint)) {
					return false;
				}
		}
		prop.tValue = collisionPoint;
		prop.intersectionPoint = r.at(collisionPoint);
		prop.normal = (prop.intersectionPoint - sphereCenter) / radius;

		prop.correctFrontalOrientation(r);

		return true;
	}

}