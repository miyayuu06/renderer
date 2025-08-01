#include "color.h"
#include <iostream>

namespace Renderer {
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

	void Color::writeColor(uint8_t* buffer, uint32_t& index, Vec3& pixel) {
		buffer[index++] = valueCorrector(pixel.r);
		buffer[index++] = valueCorrector(pixel.g);
		buffer[index++] = valueCorrector(pixel.b);
	}
}