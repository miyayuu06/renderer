#pragma once
#include "vec3.h"

namespace Renderer {
	class Ray {
	public:
		Ray(const Vec3& point, const Vec3& dir);
		const Vec3 at(double t);
		const Vec3 origin();
		const Vec3 dir();
	private:
		Vec3 _origin;
		Vec3 _direction;
	};
}