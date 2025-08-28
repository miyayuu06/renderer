#pragma once
#include "quad.h"

namespace Renderer {
	class Disk : public Quad {
	public:
		Disk(const Vec3& q, const Vec3& u, const Vec3& v, Material* m, double r);
		bool hit(const Interval& i, const Ray& r, HitProperties& prop) const;
		bool isInterior(double a, double, HitProperties& prop) const;
	private:
		double radius;
		Vec3 Q;
		Vec3 u, v;
		Vec3 w;
		Material* mat;
		AABB bbox;

		Vec3 normal;
		double D;
	};
}