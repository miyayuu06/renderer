#pragma once
#include "ray.h"
#include "interval.h"

namespace Renderer {
	class HitProperties {
	public:
		Vec3 intersectionPoint;
		Vec3 normal;
		double tValue;
		bool frontFace;

		void correctFrontalOrientation(Ray &r) {
			frontFace = (r.dir().dot(normal) > 0.0);
			normal = frontFace ? normal : -normal;
		}
	};

	class Hittable {
	public:
		virtual bool hit(Interval& i, Ray& r, HitProperties& prop) = 0;
	};
}