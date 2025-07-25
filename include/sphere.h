#pragma once

#include "vec3.h"
#include "hittable.h"

namespace Renderer {
	class Sphere : public Hittable {
	public:
		Sphere(Vec3 center, double r);
		bool hit(Interval& interval, Ray& r, HitProperties& prop);
	
	private:
		Vec3 sphereCenter;
		double radius;
	};
}