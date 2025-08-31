#pragma once
#include "hittable_list.h"

namespace Renderer {
	class Quad : public Hittable {
	public:
		Quad();
		Quad(const Vec3& q, const Vec3& u, const Vec3& v, Material* m);
		virtual void setBoundingBox();
		AABB boundingBox() const;
		bool hit(const Interval& i, const Ray& r, HitProperties& prop) const;
		virtual bool isInterior(double a, double, HitProperties& prop) const;
		static void cube(const Vec3& a, const Vec3& b, Material* m, HittableList& world);
	private:
		Vec3 Q;
		Vec3 u, v;
		Vec3 w;
		Material* mat;
		AABB bbox;

		Vec3 normal;
		double D;
	};
}