#pragma once
#include "hittable_list.h"

namespace Renderer {
	class BVH : public Hittable {
	public:
		BVH(HittableList l);

		BVH(HittableList& l, size_t start, size_t end);
		bool hit(const Interval& t, const Ray& r, HitProperties& record) const;
		AABB boundingBox() const;

	private:
		Hittable* left;
		Hittable* right;
		AABB bbox;

		static bool boxCompare(const Hittable* a, const Hittable* b, int index);
		static bool boxCompareX(const Hittable* a, const Hittable* b);
		static bool boxCompareY(const Hittable* a, const Hittable* b);
		static bool boxCompareZ(const Hittable* a, const Hittable* b);

	};
}