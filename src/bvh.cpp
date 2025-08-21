#include "bvh.h"

#include <algorithm>
#include <iostream>

namespace Renderer {
	BVH::BVH(HittableList l) : BVH(l, 0, l.objCollection.size()) {
	}

	BVH::BVH(HittableList& l, size_t start, size_t end) {
		int axis = rand() % 3;

		auto comparator = (axis == 0) ? boxCompareX : (axis == 1) ? boxCompareY : boxCompareZ;

		size_t span = end - start;
		if (span == 1) {
			left = right = l.objCollection[start];
		}
		else if (span == 2) {
			left = l.objCollection[start];
			right = l.objCollection[start + 1];
		}
		else {
			std::sort(std::begin(l.objCollection) + start, std::begin(l.objCollection) + end, comparator);

			auto mid = start + span / 2;
			left = new BVH(l, start, mid);
			right = new BVH(l, mid + 1, end);
		}

		bbox = AABB(left->boundingBox(), right->boundingBox());
	}

	bool BVH::hit(const Interval& t, const Ray& r, HitProperties& record) const {
		if (!bbox.hit(r, t)) {
			return false;
		}
		
		bool leftHit = left->hit(t, r, record);
		bool rightHit = right->hit(Interval(t.minimum, leftHit ? record.tValue : t.maximum), r, record);

		return leftHit || rightHit;
	}

	AABB BVH::boundingBox() const {
		return bbox;
	}

	bool BVH::boxCompare(const Hittable* a, const Hittable* b, int axis) {
		bool comp = a->boundingBox().axisInterval(axis).minimum < b->boundingBox().axisInterval(axis).minimum;;
		return axis == 2 ? !comp : comp;
	}

	bool BVH::boxCompareX(const Hittable* a, const Hittable* b) {
		return boxCompare(a, b, 0);
	}

	bool BVH::boxCompareY(const Hittable* a, const Hittable* b) {
		return boxCompare(a, b, 1);
	}

	bool BVH::boxCompareZ(const Hittable* a, const Hittable* b) {
		return boxCompare(a, b, 2);
	}
}