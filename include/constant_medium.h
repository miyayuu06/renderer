#pragma once
#include "hittable.h"
#include "texture.h"

namespace Renderer {
	class ConstantMedium : public Hittable {
	public:
		ConstantMedium(double den, Hittable* obj, Texture* tex);
		ConstantMedium(double den, Hittable* obj, const Vec3& albedo);
		bool hit(const Interval& i, const Ray& r, HitProperties& prop) const;
		AABB boundingBox() const;

	private:
		double density;
		Hittable* boundary;
		Material* material;
	};
}