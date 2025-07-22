#pragma once
#include "ray.h"

namespace Renderer {
	class HitProperties {
	public:
		Vec intersectionPoint;
		Vec normal;
		double tValue;
	};

	class Hittable {
	public:
		virtual bool hit(double tMin, double tMax, Ray& r, HitProperties& prop) = 0;
	};
}