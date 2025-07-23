#include "hittable_list.h"

namespace Renderer {

	HittableList::HittableList() {
		objCollection = {};
	};

	void HittableList::add(Hittable* h) {
		objCollection.push_back(h);
	}

	bool HittableList::hit(Interval& interval, Ray& r, HitProperties& prop) {
		Interval auxiliaryInterval = interval;
		HitProperties auxiliaryProp;
		bool objectCollisionProduced = false;
		
		for (Hittable* object : objCollection) {
			if (object->hit(auxiliaryInterval, r, auxiliaryProp)) {
				objectCollisionProduced = true;
				auxiliaryInterval = Interval(interval.mini(), auxiliaryProp.tValue);
				prop = auxiliaryProp;
			}
		}

		return objectCollisionProduced;
	}
}