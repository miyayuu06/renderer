#pragma once

#include "vec3.h"
#include "hittable.h"

namespace Renderer {
	class Sphere : public Hittable {
	public:
		Sphere(const Vec3 center, double r, Material* m);
		Sphere(const Vec3 p1, const Vec3 p2, double r, Material* m);
		bool hit(const Interval& interval, const Ray& r, HitProperties& prop) const;

		AABB boundingBox() const;
	
	private:
		Ray sphereCenter;
		double radius;
		Material* material;
		AABB bbox;
	};
}