#pragma once

#include "vec3.h"
#include "hittable.h"

namespace Renderer {
	class Sphere : public Hittable {
	public:
		Sphere(const Vec3 center, double r, Material* m);
		bool hit(const Interval& interval, const Ray& r, HitProperties& prop) const;
	
	private:
		Vec3 sphereCenter;
		double radius;
		Material* material;
	};
}