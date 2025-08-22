
#include "rtw_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace Renderer {
	RTW::RTW() {}

	RTW::RTW(const char* filename) {
        std::string stringFile = std::string(filename);
        if (!load(stringFile)) {
            std::cerr << "Could not load image." << std::endl;
        }
	}

    RTW::~RTW() {
        delete[] bdata;
        stbi_image_free(fdata);
    }

	bool RTW::load(const std::string& filename) {
        int n = bpp;
        fdata = stbi_loadf(filename.c_str(), &width, &height, &n, bpp);
        
        if (fdata == nullptr) {
            return false;
        }

        convertToBytes();

        return true;
	}

    const unsigned char* RTW::pixelData(int i, int j) const {
        static unsigned char mag[] = {255, 0, 255};
        if (bdata == nullptr) {
            return mag;
        }

        i = clamp(i, 0, width);
        j = clamp(j, 0, height);

        return bdata + (j * width + i) * bpp;
    }

    int RTW::w() const {
        return width;
    }

    int RTW::h() const {
        return height;
    }

    int RTW::clamp(int x, int low, int high) {
        if (x < low) return low;
        if (x >= high) return high;
        return x;
    }

    unsigned char RTW::floatToByte(float value) {
        if (value <= 0.0)
            return 0;
        if (1.0 <= value)
            return 255;
        return static_cast<unsigned char>(256.0 * value);
    }

    void RTW::convertToBytes() {

        int total_bytes = width * height * bpp;
        bdata = new unsigned char[total_bytes];

        for (int i = 0; i < total_bytes; i++) {
            bdata[i] = floatToByte(fdata[i]);
        }
    }
}