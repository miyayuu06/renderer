#pragma once
#include "vec3.h"
#include <cstdint>

namespace Renderer {
	class Color {
	public:
		static void writeColor(uint8_t* buffer, uint32_t& index, Vec& pixel);
		static int valueCorrector(double x);
	};
}