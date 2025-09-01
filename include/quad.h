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

	private:
		Vec3 Q;
		Vec3 u, v;
		Vec3 w;
		Material* mat;
		AABB bbox;

		Vec3 normal;
		double D;
	};

	inline HittableList* box(const Vec3& a, const Vec3& b, Material* mat) {
		Vec3 min = Vec3(fmin(a.x, b.x), fmin(a.y, b.y), fmin(a.z, b.z));
		Vec3 max = Vec3(fmax(a.x, b.x), fmax(a.y, b.y), fmax(a.z, b.z));

		Vec3 x = Vec3(max.x - min.x, 0, 0);
		Vec3 y = Vec3(0, max.y - min.y, 0);
		Vec3 z = Vec3(0, 0, max.z - min.z);

		HittableList* sides = new HittableList();

		sides->add(new Quad(Vec3(min.x, min.y, max.z), y, x, mat));
		sides->add(new Quad(Vec3(max.x, min.y, max.z), y, -z, mat));
		sides->add(new Quad(Vec3(max.x, min.y, min.z), y, -x, mat));
		sides->add(new Quad(Vec3(min.x, min.y, min.z), z, y, mat));
		sides->add(new Quad(Vec3(min.x, max.y, max.z), -z, x, mat));
		sides->add(new Quad(Vec3(min.x, min.y, min.z), z, x, mat));

		return sides;
	}
}