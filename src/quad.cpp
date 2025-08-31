#include "quad.h"

namespace Renderer {
	Quad::Quad() {}

	Quad::Quad(const Vec3& q, const Vec3& u, const Vec3& v, Material* m) : Q(q), u(u), v(v), mat(m) {
		Vec3 n = u.cross(v);
		normal = n.norm();
		D = normal.dot(Q);
		w = n / (n.dot(n));
		setBoundingBox();
	}

	void Quad::setBoundingBox() {
		AABB b1 = AABB(Q, Q + u + v);
		AABB b2 = AABB(Q + u, Q + v);
		bbox = AABB(b1, b2);
	}

	AABB Quad::boundingBox() const {
		return bbox;
	}

	bool Quad::hit(const Interval& i, const Ray& r, HitProperties& prop) const {
		double denominator = normal.dot(r.dir());

		if (denominator < 1e-8) {
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

	bool Quad::isInterior(double a, double b, HitProperties& prop) const {
		if (a < 0.0 || a > 1.0 || b < 0.0 || b > 1.0) {
			return false;
		}

		prop.u = a;
		prop.v = b;
		return true;
	}

	Hittable* Quad::box(const Vec3& a, const Vec3& b, Material* mat) {
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