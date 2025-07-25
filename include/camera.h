#pragma once

#include "hittable_list.h"

namespace Renderer {
	class Camera {
	public:
		Camera();
		Vec3 center;
		const double aspectRatio = 16.0 / 9.0;
		const int width = 1920;

		void initialize();
		void render(HittableList& list);
	private:
		int height;
		int CHANNEL_NUM;
		Vec3 pixel00;
		Vec3 upperLeftCorner;
		Vec3 deltaH;
		Vec3 deltaV;

		Ray get_ray();
		Vec3 ray_color(HittableList& world, Ray& r);
	};
}