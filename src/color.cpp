#include "color.h"
#include <iostream>

namespace Renderer {

	double Color::linearGamma(double comp) {
		return comp < 0.0 ? 0.0 : sqrt(comp);
	}

	int Color::valueCorrector(double x) {
		int result = int(x * 255);
		if (result < 0) {
			return 0;
		}
		if (result > 255) {
			return 255;
		}
		return result;
	}

	void Color::writeColor(uint8_t* buffer, uint32_t index, Vec3& pixel) {
		pixel.r = linearGamma(pixel.r);
		pixel.g = linearGamma(pixel.g);
		pixel.b = linearGamma(pixel.b);

		buffer[index++] = valueCorrector(pixel.r);
		buffer[index++] = valueCorrector(pixel.g);
		buffer[index++] = valueCorrector(pixel.b);
	}
}