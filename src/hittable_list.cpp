#include "hittable_list.h"

namespace Renderer {

	HittableList::HittableList() {
		objCollection = {};
	};

	void HittableList::add(Hittable* h) {
		objCollection.push_back(h);
	}

	bool HittableList::hit(double tmin, double tmax, Ray& r, HitProperties& prop) {
		double closestSoFar = tmax;
		HitProperties auxiliaryProp;
		bool objectCollisionProduced = false;
		
		for (Hittable* object : objCollection) {
			if (object->hit(tmin, closestSoFar, r, auxiliaryProp)) {
				objectCollisionProduced = true;
				closestSoFar = auxiliaryProp.tValue;
				prop = auxiliaryProp;
			}
		}

		return objectCollisionProduced;
	}
}