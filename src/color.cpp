#include "color.h"
#include <iostream>

namespace Renderer {
	void Color::writeColor(uint8_t* buffer, uint32_t& index, Vec& pixel) {
		int r = int(pixel[0] * 255.999);
		int g = int(pixel[1] * 255.999);
		int b = int(pixel[2] * 255.999);
		
		buffer[index++] = r;
		buffer[index++] = g;
		buffer[index++] = b;
	}
}