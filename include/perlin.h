#pragma once

#include "vec3.h"

namespace Renderer {
	class Perlin {
	public:
		Perlin();
		double noise(const Vec3& p) const;
	private:
		double randFloat[256];
		int px[256];
		int py[256];
		int pz[256];
		static void generateRandomPerlin(int* p);
		static void permute(int* p, int n);
		static double trilinearInterpolation(double c[2][2][2], double u, double v, double w);
	};
}