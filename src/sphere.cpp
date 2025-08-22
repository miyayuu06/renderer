#include "sphere.h"
#include <cmath>

#define PI 3.14159265

namespace Renderer {
	Sphere::Sphere(const Vec3 center, double r, Material* m) {
		sphereCenter = Ray(center, Vec3());
		radius = r;
		material = m;
		bbox = AABB(center - Vec3(r), center + Vec3(r));
	}

	Sphere::Sphere(const Vec3 p1, const Vec3 p2, double r, Material* m) {
		sphereCenter = Ray(p1, p2 - p1);
		radius = r;
		material = m;

		Vec3 radiusVec(r);
		AABB box1(sphereCenter.at(0) - radiusVec, sphereCenter.at(0) + radiusVec);
		AABB box2(sphereCenter.at(1) - radiusVec, sphereCenter.at(1) + radiusVec);
		bbox = AABB(box1, box2);
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
		prop.correctFrontalOrientation(r);
		getUV(prop.normal, prop.u, prop.v);

		prop.mat = material;

		return true;
	}

	void Sphere::getUV(const Vec3& p, double& u, double& v) {
		double phi = std::atan2(p.z, p.x) + PI;
		double theta = std::acos(p.y);
		
		u = phi / (2 * PI);
		v = 1 - theta / PI;
	}

	AABB Sphere::boundingBox() const {
		return bbox;
	}

}