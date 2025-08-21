#include "bvh.h"

namespace Renderer {
	BVH::BVH(HittableList l) {

	}

	BVH::BVH(HittableList& l, size_t start, size_t end) {

	}

	bool BVH::hit(Interval t, const Ray& r, HitProperties& record) {
		if (!bbox.hit(r, t)) {
			return false;
		}
		
		bool leftHit = left->hit(t, r, record);
		bool rightHit = right->hit(Interval(t.minimum, leftHit ? record.tValue : t.maximum), r, record);

		return leftHit || rightHit;
	}
}