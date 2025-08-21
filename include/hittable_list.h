#pragma once

#include "hittable.h"
#include <vector>

namespace Renderer {
	class HittableList : public Hittable {
	public:
		std::vector<Hittable*> objCollection;

		HittableList();
		HittableList(Hittable* h);

		void add(Hittable* h);

		bool hit(const Interval& interval, const Ray &r, HitProperties& prop) const;

		AABB boundingBox() const;

	private:
		AABB bbox;
	};
}