#pragma once

#include "hittable.h"
#include <vector>

namespace Renderer {
	class HittableList : public Hittable {
	public:
		HittableList();

		void add(Hittable* h);

		bool hit(Interval& interval, Ray &r, HitProperties& prop);

	private:
		std::vector<Hittable*> objCollection;
	};
}