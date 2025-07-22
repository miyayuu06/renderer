#pragma once

#include "vec3.h"
#include "hittable.h"

namespace Renderer {
	class Sphere : public Hittable {
	public:
		Sphere(Vec center, double r);
		bool hit(double tmin, double tmax, Ray& r, HitProperties& prop);
	
	private:
		Vec sphereCenter;
		double radius;
	};
}