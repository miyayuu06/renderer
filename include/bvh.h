#pragma once
#include "hittable_list.h"

namespace Renderer {
	class BVH : public Hittable {
	public:
		BVH(HittableList l);

		BVH(HittableList& l, size_t start, size_t end);
		bool hit(Interval t, const Ray& r, HitProperties& record);
		AABB boundingBox() const;

	private:
		Hittable* left;
		Hittable* right;
		AABB bbox;
	};
}