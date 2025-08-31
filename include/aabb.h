#pragma once
#include "interval.h"
#include "ray.h"


namespace Renderer {
	class AABB {
	public:
		Interval x, y, z;
		AABB();
		AABB(const Interval& x, const Interval& y, const Interval& z);
		AABB(const Vec3& a, const Vec3& b);
		AABB(const AABB& a, const AABB& b);

		const Interval& axisInterval(int n) const;

		bool hit(const Ray& r, Interval rayT) const;

		AABB operator+(const Vec3& offset);

	private:
		void padToMinimum();
	};
}