#include "constant_medium.h"
#include "renderer_utils.h"
#include "material.h"
#include <limits>

namespace Renderer {
	ConstantMedium::ConstantMedium(double den, Hittable* obj, Texture* tex) : density(den), boundary(obj), mat(new Isotropic(tex)) {
	}

	ConstantMedium::ConstantMedium(double den, Hittable* obj, const Vec3& albedo) : density(den), boundary(obj), mat(new Isotropic(albedo)) {}

	bool ConstantMedium::hit(const Interval& i, const Ray& r, HitProperties& prop) const {
		const double inf = std::numeric_limits<double>::infinity();

		HitProperties a, b;

		if (!boundary->hit(Interval(-inf, inf), r, a)) {
			return false;
		}

		if (!boundary->hit(Interval(a.tValue + 0.0001, inf), r, b)) {
			return false;
		}

		a.tValue = (a.tValue < i.minimum) ? i.minimum : a.tValue;
		b.tValue = (b.tValue > i.maximum) ? i.maximum : b.tValue;

		if (a.tValue >= b.tValue) {
			return false;
		}

		a.tValue = (a.tValue < 0) ? 0 : a.tValue;

		if (a.tValue >= b.tValue) {
			return false;
		}

		double rayLength = r.dir().length();
		double boundaryDistance = (b.tValue - a.tValue) * rayLength;
		double hitDistance = -(1 / density) * log(fmax(1e-12, randomRealNumber(0.0, 1.0)));

		if (hitDistance > boundaryDistance) {
			return false;
		}

		prop.tValue = a.tValue + hitDistance / rayLength;
		prop.intersectionPoint = r.at(prop.tValue);
		prop.normal = Vec3(1.0, 0, 0);
		prop.frontFace = true;
		prop.mat = mat;

		return true;
	}

	AABB ConstantMedium::boundingBox() const {
		return boundary->boundingBox();
	}
}