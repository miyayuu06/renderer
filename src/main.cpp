// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

int main()
{
    const char* file = "C:/Users/yunaf/Desktop/testimage.png";
    const int width = 512;
    const int height = 512;
    const int CHANNEL_NUM = 3;

    uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

    uint32_t index = 0;

    for (uint32_t i = 0; i < width; i++) {
        for (uint32_t j = 0; j < height / 2; j++) {
            pixels[index++] = 255;
            pixels[index++] = 192;
            pixels[index++] = 203;
        }
    }

    for (uint32_t i = 0; i < width; i++) {
        for (uint32_t j = height / 2; j < height; j++) {
            pixels[index++] = 255;
            pixels[index++] = 238;
            pixels[index++] = 140;
        }
    }

    if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
        std::cout << "Hubo un error.\n";
    }
    std::cout << "Hello World!\n";
    delete[] pixels;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
