#include "perlin.h"
#include "renderer_utils.h"

namespace Renderer {
	Perlin::Perlin() {
		for (int i = 0; i < 256; i++) {
			randFloat[i] = random();
		}

		generateRandomPerlin(px);
		generateRandomPerlin(py);
		generateRandomPerlin(pz);
	}

	double Perlin::noise(const Vec3& p) const {
		double u = p.x - floor(p.x);
		double v = p.y - floor(p.y);
		double w = p.z - floor(p.z);

		u = u * u * (3 - 2 * u);
		v = v * v * (3 - 2 * v);
		w = w * w * (3 - 2 * w);

		int i = int(floor(p.x));
		int j = int(floor(p.y));
		int k = int(floor(p.z));

		double c[2][2][2];

		for (int di = 0; di < 2; di++) {
			for (int dj = 0; dj < 2; dj++) {
				for (int dk = 0; dk < 2; dk++) {
					c[di][dj][dk] = randFloat[px[(i + di) & 255] ^ 
						px[(j + dj) & 255] ^ px[(k + dk) & 255]];
				}
			}
		}

		return trilinearInterpolation(c, u, v, w);
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

	double Perlin::trilinearInterpolation(double c[2][2][2], double u, double v, double w) {
		double accumulation = 0.0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					accumulation += (i * u + (1 - i) * (1 - u)) *
						(j * v + (1 - j) * (1 - v)) *
						(k * w + (1 - w) * (1 - k)) *
						c[i][j][k];
				}
			}
		}
		return accumulation;
	}
}