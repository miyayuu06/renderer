#pragma once

#include "vec3.h"

namespace Renderer {
	class Perlin {
	public:
		Perlin();
		double noise(const Vec3& p) const;
		double turbulence(const Vec3& p, int depth) const;
	private:
		Vec3 randVec[256];
		int px[256];
		int py[256];
		int pz[256];
		static void generateRandomPerlin(int* p);
		static void permute(int* p, int n);
		static double trilinearInterpolation(Vec3 c[2][2][2], double u, double v, double w);
	};
}