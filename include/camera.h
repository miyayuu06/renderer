#pragma once

#include "hittable_list.h"

namespace Renderer {
	class Camera {
	public:
		Vec3 center;
		void initialize();
		void render();
	private:
		Ray get_ray();
		Vec3 ray_color(HittableList& world, Ray& r);
	};
}