#pragma once

#include "hittable_list.h"

#include <mutex>
#include <queue>

namespace Renderer {
	class Camera {
	public:
		Camera();
		Vec3 center;
		double aspectRatio;
		int width;
		int samplesPerPixel;
		int rayRecursionLimit;
		double verticalViewAngle;

		double defocusAngle;
		double focusDistance = 10;
		
		Vec3 lookfrom;
		Vec3 lookat;
		Vec3 up;

		Vec3 background;

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

		Vec3 focusDiskH;
		Vec3 focusDiskV;
		
		Vec3 u;
		Vec3 v;
		Vec3 w;

		std::mutex m;
		std::atomic<int> printedRows;

		Vec3 ray_color(const HittableList& world, const Ray& r, int depth);
		Ray get_ray(int i, int j) const;
		Vec3 sampleSquare() const;
		Vec3 diskSample() const;
		void sectionRender(const HittableList& scenery, uint8_t* pixels);
	};
}