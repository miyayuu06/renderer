#pragma once
#include <string>

namespace Renderer {
	class RTW {
	public:
		RTW();
		RTW(const char* filename);
		~RTW();
		bool load(const std::string& filename);

		int h() const;
		int w() const;

		const unsigned char* pixelData(int i, int j) const;

	private:
		const int bpp = 3;
		float* fdata;
		unsigned char* bdata;
		int width;
		int height;
		int bps;

		static int clamp(int x, int low, int high);
		static unsigned char floatToByte(float value);
		void convertToBytes();

	};
}