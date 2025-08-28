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
		int x = int(4 * p.x) & 255;
		int y = int(4 * p.y) & 255;
		int z = int(4 * p.z) & 255;

		return randFloat[x ^ y ^ z];
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
}