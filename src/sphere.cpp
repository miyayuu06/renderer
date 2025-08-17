#include "sphere.h"
#include <cmath>

namespace Renderer {
	Sphere::Sphere(const Vec3 center, double r, Material* m) {
		sphereCenter = Ray(center, Vec3());
		radius = r;
		material = m;
	}

	Sphere::Sphere(const Vec3 p1, const Vec3 p2, double r, Material* m) {
		sphereCenter = Ray(p1, p2 - p1);
		radius = r;
		material = m;
	}

	bool Sphere::hit(const Interval& interval, const Ray& r, HitProperties& prop) const {
		Vec3 currentCenter = sphereCenter.at(r.tm());
		Vec3 centerDistance = currentCenter - r.origin();
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
		prop.normal = (prop.intersectionPoint - currentCenter) / radius;
		prop.mat = material;

		prop.correctFrontalOrientation(r);

		return true;
	}

}