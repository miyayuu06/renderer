#include "texture.h"
#include "interval.h"
#include <cmath>

namespace Renderer {
	Solid::Solid(const Vec3& alb) : albedo(alb) {}

	Solid::Solid(double r, double g, double b) : albedo(Vec3(r,g,b)) {}

	Vec3 Solid::value(double u, double v, const Vec3& p) const {
		return albedo;
	}

	Checkered::Checkered(double scale, Texture* e, Texture* o) : inv(1.0 / scale), even(e), odd(o) {}

	Checkered::Checkered(double scale, const Vec3& e, const Vec3& o) : inv(1.0 / scale) {
		even = new Solid(e);
		odd = new Solid(o);
	}


	Vec3 Checkered::value(double u, double v, const Vec3& p) const {
		int x = int(std::floor(p.x * inv));
		int y = int(std::floor(p.y * inv));
		int z = int(std::floor(p.z * inv));

		bool isEven = ((x + y + z) % 2) == 0;

		return isEven ? even->value(u, v, p) : odd->value(u, v, p);
	}


	ImageTexture::ImageTexture(const char* filename) : img(RTW(filename)){}

	Vec3 ImageTexture::value(double u, double v, const Vec3& p) const {
		if (img.h() <= 0) {
			return Vec3(0, 1, 1);
		}

		u = Interval(0, 1).clamp(u);
		v = Interval(0, 1).clamp(v);

		int i = int(u * img.w());
		int j = int((1.0 - v) * img.h());
		const unsigned char *pixel = img.pixelData(i, j);

		double scale = 1.0 / 255.0;
		return Vec3(pixel[0], pixel[1], pixel[2]) * scale;
	}
}