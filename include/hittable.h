#pragma once
#include "aabb.h"

namespace Renderer {
	class Material;

	class HitProperties {
	public:
		Vec3 intersectionPoint;
		Vec3 normal;
		Material* mat;
		double tValue;
		double u;
		double v;
		bool frontFace;

		void correctFrontalOrientation(const Ray &r) {
			frontFace = (r.dir().dot(normal) < 0.0);
			normal = frontFace ? normal : -normal;
		}
	};

	class Hittable {
	public:
		virtual bool hit(const Interval& i, const Ray& r, HitProperties& prop) const = 0;
		virtual AABB boundingBox() const = 0;
	};
}