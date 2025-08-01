#pragma once
#include "ray.h"
#include "interval.h"

namespace Renderer {
	class Material;

	class HitProperties {
	public:
		Vec3 intersectionPoint;
		Vec3 normal;
		Material* mat;
		double tValue;
		bool frontFace;

		void correctFrontalOrientation(const Ray &r) {
			frontFace = (r.dir().dot(normal) < 0.0);
			normal = frontFace ? normal : -normal;
		}
	};

	class Hittable {
	public:
		virtual bool hit(const Interval& i, const Ray& r, HitProperties& prop) const = 0;
	};
}