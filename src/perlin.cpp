#include "perlin.h"
#include "renderer_utils.h"

namespace Renderer {
	Perlin::Perlin() {
		for (int i = 0; i < 256; i++) {
			randVec[i] = Vec3::random(-1, 1).norm();
		}

		generateRandomPerlin(px);
		generateRandomPerlin(py);
		generateRandomPerlin(pz);
	}

	double Perlin::noise(const Vec3& p) const {
		double u = p.x - floor(p.x);
		double v = p.y - floor(p.y);
		double w = p.z - floor(p.z);

		int i = int(floor(p.x));
		int j = int(floor(p.y));
		int k = int(floor(p.z));

		Vec3 c[2][2][2];

		for (int di = 0; di < 2; di++) {
			for (int dj = 0; dj < 2; dj++) {
				for (int dk = 0; dk < 2; dk++) {
					c[di][dj][dk] = randVec[px[(i + di) & 255] ^ 
						px[(j + dj) & 255] ^ px[(k + dk) & 255]];
				}
			}
		}

		return trilinearInterpolation(c, u, v, w);
	}

	double Perlin::turbulence(const Vec3& p, int depth) const {
		double accum = 0.0;
		Vec3 temp = p;
		double weight = 1.0;

		for (int i = 0; i < depth; i++) {
			accum += weight * noise(temp);
			weight *= 0.5;
			temp *= 2;
		}

		return fabs(accum);
	}

	void Perlin::generateRandomPerlin(int* p) {
		for (int i = 0; i < 256; i++) {
			p[i] = i;
		}

		permute(p, 256);
	}

	void Perlin::permute(int* p, int n) {
		for (int i = 0; i < n; i++) {
			int randomIndex = rand() % n;
			int aux = p[i];
			p[i] = p[randomIndex];
			p[randomIndex] = aux;
		}
	}

	double Perlin::trilinearInterpolation(Vec3 c[2][2][2], double u, double v, double w) {
		double uu = u * u * (3 - 2 * u);
		double vv = v * v * (3 - 2 * v);
		double ww = w * w * (3 - 2 * w);

		double accumulation = 0.0;

		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					Vec3 weight(u - i, v - j, w - k);
					accumulation += (i * uu + (1 - i) * (1 - uu)) *
						(j * vv + (1 - j) * (1 - vv)) *
						(k * ww + (1 - ww) * (1 - k)) *
						c[i][j][k].dot(weight);
				}
			}
		}
		return accumulation;
	}
}