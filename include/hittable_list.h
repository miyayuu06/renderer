#pragma once

#include "hittable.h"
#include <vector>

namespace Renderer {
	class HittableList : public Hittable {
	public:
		HittableList();

		void add(Hittable* h);

		bool hit(const Interval& interval, const Ray &r, HitProperties& prop) const;

	private:
		std::vector<Hittable*> objCollection;
	};
}