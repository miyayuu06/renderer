#include "aabb.h"

namespace Renderer {
	AABB::AABB() {}

	AABB::AABB(const Interval& x, const Interval& y, const Interval& z) : x(x), y(y), z(z) {
		padToMinimum();
	}

	AABB::AABB(const Vec3& a, const Vec3& b) {
		x = a[0] <= b[0] ? Interval(a[0], b[0]) : Interval(b[0], a[0]);
		y = a[1] <= b[1] ? Interval(a[1], b[1]) : Interval(b[1], a[1]);
		z = a[2] <= b[2] ? Interval(a[2], b[2]) : Interval(b[2], a[2]);
		padToMinimum();
	}

	AABB::AABB(const AABB& a, const AABB& b) {
		x = Interval(a.x, b.x);
		y = Interval(a.y, b.y);
		z = Interval(a.z, b.z);
	}

	const Interval& AABB::axisInterval(int n) const {
		if (n == 1) {
			return y;
		}

		return n ? z : x;
	}

	bool AABB::hit(const Ray& r, Interval rayT) const {
		Vec3 rayOrigin = r.origin();
		Vec3 rayDir = r.dir();

		for (int i = 0; i < 3; i++) {
			const Interval& axis = axisInterval(i);
			const double inv = 1.0 / rayDir[i];
			
			double t0 = (axis.mini() - rayOrigin[i]) * inv;
			double t1 = (axis.maxi() - rayOrigin[i]) * inv;

			if (t0 < t1) {
				if (t0 > rayT.minimum) {
					rayT.minimum = t0;
				}
				if (t1 < rayT.maximum) {
					rayT.maximum = t1;
				}
			}
			else {
				if (t1 > rayT.minimum) {
					rayT.minimum = t1;
				}
				if (t0 < rayT.maximum) {
					rayT.maximum = t0;
				}
			}
			if (rayT.maximum < rayT.minimum) {
				return false;
			}
		}

		return true;

	}

	void AABB::padToMinimum() {
		double delta = 0.0001;

		if (x.maximum - x.minimum < delta) {
			x = x.expand(delta);
		}
		if (y.maximum - y.minimum < delta) {
			y = y.expand(delta);
		}
		if (z.maximum - z.minimum < delta) {
			z = z.expand(delta);
		}
	}
}