// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "sphere.h"
#include "camera.h"

using namespace Renderer;

//Vec3 ray_color(HittableList& scenery, Ray& r) {
//    HitProperties record;
//    Interval rangeOfRender(0.0001, INFINITY);
//    if (scenery.hit(rangeOfRender, r, record)) {
//        return (record.normal + Vec3(1.0, 1.0, 1.0)) * 0.5;
//    }
//
//    // Background
//    const Vec3 unitVec3tor = r.dir().norm();
//    double a = (unitVec3tor.y + 1.0) * 0.5;
//    return (Vec3(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec3(0.5, 0.7, 1.0) * a);
//}

int main()
{

    HittableList scenery;

    for (int i = 0; i < 7; i++) {
        double x = ((rand() % 10000) / 10000.0 - 0.5) * 10.0;
        double y = ((rand() % 10000) / 10000.0 - 0.5) * 10.0;
        double z = ((rand() % 10000) / 10000.0) * 10.0 + 1.0;
        scenery.add(new Sphere(Vec3(x, y, z), (rand() % 11) / 10.0));
    }

    Camera camera;
    camera.initialize();
    camera.render(scenery);

    //const double aspectRatio = 16.0 / 9.0;
    //const int width = 1920;
    //const int height = int(width / aspectRatio);
    //const int CHANNEL_NUM = 3;

    //// Camera

    //double near = 1.0;
    //double viewportHeight = 2.0;
    //double viewportWidth = viewportHeight * (double(width) / height);
    //const Vec3 cameraCenter(0.0, 0.0, 0.0);

    //// Viewport vectors

    //Vec3 viewportHorizontal(viewportWidth, 0.0, 0.0);
    //Vec3 viewportVertical(0.0, -viewportHeight, 0.0);
    //Vec3 deltaH = viewportHorizontal * (1.0 / width);
    //Vec3 deltaV = viewportVertical * (1.0 / height);

    //// Upper left coordinates

    //Vec3 upperLeftCorner = cameraCenter + Vec3(0.0, 0.0, near) + (viewportHorizontal * -0.5) + (viewportVertical * -0.5);
    //Vec3 pixel00 = upperLeftCorner + (deltaH + deltaV) * 0.5;

    //uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

    //uint32_t index = 0;

    //// Scene

    ////scenery.add(new Sphere(Vec3(0, 0, 1), 0.5));
    ////scenery.add(new Sphere(Vec3(0, -100.5, -1), 100));

    //for (uint32_t i = 0; i < height; i++) {
    //    std::cout << "Rendering row: " << i << std::endl;
    //    for (uint32_t j = 0; j < width; j++) {
    //        const Vec3 pixel = pixel00 + (deltaV * i) + (deltaH * j);
    //        const Vec3 rayDirection = pixel - cameraCenter;
    //        Ray ray(cameraCenter, rayDirection);

    //        Vec3 color = ray_color(scenery, ray);

    //        Color::writeColor(pixels, index, color);
    //    }
    //}

    //if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
    //    std::cout << "Hubo un error.\n";
    //}
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
