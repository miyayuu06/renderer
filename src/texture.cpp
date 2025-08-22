#include "texture.h"
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
		return (x + y + z) % 2 ? odd->value(u, v, p) : even->value(u, v, p);
	}
}