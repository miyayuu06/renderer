#include "hittable_list.h"

namespace Renderer {

	HittableList::HittableList() {
		objCollection = {};
	};

	void HittableList::add(Hittable* h) {
		objCollection.push_back(h);
		bbox = AABB(bbox, h->boundingBox());
	}

	AABB HittableList::boundingBox() const {
		return bbox;
	}

	bool HittableList::hit(const Interval& interval, const Ray& r, HitProperties& prop) const {
		bool objectCollisionProduced = false;
		double closestSoFar = interval.maxi();
		HitProperties auxiliaryProp;
		
		
		for (Hittable* object : objCollection) {
			if (object->hit(Interval(interval.mini(), closestSoFar), r, auxiliaryProp)) {
				objectCollisionProduced = true;
				closestSoFar = auxiliaryProp.tValue;
				prop = auxiliaryProp;
			}
		}

		return objectCollisionProduced;
	}
}