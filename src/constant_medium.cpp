#include "constant_medium.h"
#include "renderer_utils.h"
#include "material.h"
#include "hittable_list.h"
#include <limits>

namespace Renderer {
	ConstantMedium::ConstantMedium(double den, Hittable* obj, Texture* tex) : density(den), boundary(obj), material(new Isotropic(tex)) {
	}

	ConstantMedium::ConstantMedium(double den, Hittable* obj, const Vec3& albedo) : density(den), boundary(obj), material(new Isotropic(albedo)) {}

	bool ConstantMedium::hit(const Interval& i, const Ray& r, HitProperties& prop) const {
		const double inf = std::numeric_limits<double>::infinity();

		HitProperties a, b;

		if (!boundary->hit(Interval(-inf, inf), r, a)) {
			return false;
		}

		if (!boundary->hit(Interval(a.tValue + 0.0001, inf), r, b)) {
			return false;
		}

		if (a.tValue < i.minimum) {
			a.tValue = i.minimum;
		}

		if (b.tValue > i.maximum) {
			b.tValue = i.maximum;
		}

		if (a.tValue >= b.tValue) {
			return false;
		}

		if (a.tValue < 0) {
			a.tValue = 0;
		}

		if (a.tValue >= b.tValue) {
			return false;
		}

		auto boundaryDistance = (b.tValue - a.tValue);
		auto hitDistance = -(1 / density) * log(fmax(1e-12, randomRealNumber(0.0, 1.0)));

		if (hitDistance > boundaryDistance) {
			return false;
		}

		prop.tValue = a.tValue + hitDistance;
		prop.intersectionPoint = r.at(prop.tValue);
		prop.normal = Vec3(1, 0, 0);
		prop.frontFace = true;
		prop.mat = material;

		return true;
	}

	AABB ConstantMedium::boundingBox() const {
		return boundary->boundingBox();
	}
}