#pragma once

#include "hittable_list.h"

namespace Renderer {
	class Camera {
	public:
		Camera();
		Vec3 center;
		double aspectRatio;
		int width = 1920;
		int samplesPerPixel;

		void initialize();
		void render(const HittableList& list);
	private:
		int height;
		int CHANNEL_NUM;
		double samplePixelProportion;
		Vec3 pixel00;
		Vec3 upperLeftCorner;
		Vec3 deltaH;
		Vec3 deltaV;

		Vec3 ray_color(const HittableList& world, const Ray& r);
		Ray get_ray(int i, int j) const;
		Vec3 sampleSquare() const;
	};
}