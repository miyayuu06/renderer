#include "disk.h"
#include <cmath>

namespace Renderer {
	Disk::Disk(const Vec3& q, const Vec3& u, const Vec3& v, Material* m, double r) : Q(q), u(u), v(v), mat(m), radius(r) {
		Vec3 n = u.cross(v);
		normal = n.norm();
		D = normal.dot(Q);
		w = n / (n.dot(n));
		setBoundingBox();
	}

	bool Disk::hit(const Interval& i, const Ray& r, HitProperties& prop) const {
		double denominator = normal.dot(r.dir());

		if (fabs(denominator) < 1e-8) {
			return false;
		}
		double t = (D - normal.dot(r.origin())) / denominator;
		if (!i.belongs(t)) {
			return false;
		}

		Vec3 intersection = r.at(t);
		prop.intersectionPoint = intersection;
		prop.normal = normal;
		prop.mat = mat;
		prop.tValue = t;
		prop.correctFrontalOrientation(r);

		Vec3 p = intersection - Q;
		double alpha = w.dot(p.cross(v));
		double beta = w.dot(u.cross(p));

		if (!isInterior(alpha, beta, prop)) {
			return false;
		}

		return true;
	}

	bool Disk::isInterior(double a, double b, HitProperties& prop) const {
		if (!((a * a + b * b) <= (radius*radius))) {
			return false;
		}

		prop.u = a;
		prop.v = b;
		return true;
	}
}