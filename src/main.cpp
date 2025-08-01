// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "renderer_utils.h"
#include "sphere.h"
#include "camera.h"

using namespace Renderer;

int main()
{

    HittableList scenery;

    for (int i = 0; i < 4; i++) {
        double x = ((rand() % 10000) / 10000.0 - 0.5) * 10.0;
        double y = ((rand() % 10000) / 10000.0 - 0.5) * 10.0;
        double z = ((rand() % 10000) / 10000.0) * 10.0 + 1.0;
        scenery.add(new Sphere(Vec3(x, y, z), (rand() % 11) / 10.0));
    }

    Camera cam;
    cam.width = 1920;
    cam.aspectRatio = 16.0 / 9.0;
    cam.samplesPerPixel = 50;

    cam.initialize();
    cam.render(scenery);

}