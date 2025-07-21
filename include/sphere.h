#pragma once

#include "vec3.h"

namespace Renderer {
	class Sphere {
	public:
		Sphere(Vec center, double r);
		Vec sphereCenter;
		double radius;
	};
}