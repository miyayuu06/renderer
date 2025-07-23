// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

using namespace Renderer;

Vec ray_color(HittableList& scenery, Ray& r) {
    HitProperties record;
    if (scenery.hit(0.0001, INFINITY, r, record)) {
        return (record.normal + Vec(1.0, 1.0, 1.0)) * 0.5;
    }

    // Background
    Vec unitVector = r.dir().norm();
    double a = (unitVector.y + 1.0) * 0.5;
    return (Vec(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec(0.5, 0.7, 1.0) * a);
}

int main()
{
    //const char* file = "C:/Users/yunaf/Desktop/testimage.png";
    const double aspectRatio = 16.0 / 9.0;
    const int width = 1920;
    const int height = int(width / aspectRatio);
    const int CHANNEL_NUM = 3;

    // Camera

    double near = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(width) / height);
    Vec cameraCenter(0.0, 0.0, 0.0);

    // Viewport vectors

    Vec viewportHorizontal(viewportWidth, 0.0, 0.0);
    Vec viewportVertical(0.0, -viewportHeight, 0.0);
    Vec deltaH = viewportHorizontal * (1.0 / width);
    Vec deltaV = viewportVertical * (1.0 / height);

    // Upper left coordinates

    Vec upperLeftCorner = cameraCenter + Vec(0.0, 0.0, near) + (viewportHorizontal * -0.5) + (viewportVertical * -0.5);
    Vec pixel00 = upperLeftCorner + (deltaH + deltaV) * 0.5;

    uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

    uint32_t index = 0;

    // Scene

    HittableList scenery;
    scenery.add(new Sphere(Vec(0, 0, 1), 0.5));
    scenery.add(new Sphere(Vec(0, -100.5, -1), 100));

    for (uint32_t i = 0; i < height; i++) {
        //std::cout << "Rendering row: " << i << std::endl;
        for (uint32_t j = 0; j < width; j++) {
            Vec pixel = pixel00 + (deltaV * i) + (deltaH * j);
            Vec rayDirection = pixel + (-cameraCenter);
            Ray ray(cameraCenter, rayDirection);

            Vec color = ray_color(scenery, ray);

            Color::writeColor(pixels, index, color);
        }
    }

    if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
        std::cout << "Hubo un error.\n";
    }

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
