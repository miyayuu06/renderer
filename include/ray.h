#pragma once
#include "vec3.h"

namespace Renderer {
	class Ray {
	public:
		Ray(const Vec& point, const Vec& dir);
		Vec at(double t);
		Vec origin();
		Vec dir();
	private:
		Vec _origin;
		Vec _direction;
	};
}