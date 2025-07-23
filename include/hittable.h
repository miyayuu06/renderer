#pragma once
#include "ray.h"

namespace Renderer {
	class HitProperties {
	public:
		Vec intersectionPoint;
		Vec normal;
		double tValue;
		bool frontFace;

		void correctFrontalOrientation(Ray &r) {
			frontFace = r.dir().dot(normal) > 0.0;
			normal = frontFace ? normal : -normal;
		}
	};

	class Hittable {
	public:
		virtual bool hit(double tMin, double tMax, Ray& r, HitProperties& prop) = 0;
	};
}