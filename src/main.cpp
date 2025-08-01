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

    scenery.add(new Sphere(Vec3(0, -100.5, 1), 100));
    scenery.add(new Sphere(Vec3(0, 0, 1), 0.5));

    Camera cam;
    cam.width = 800;
    cam.aspectRatio = 16.0 / 9.0;
    cam.samplesPerPixel = 20;
    cam.rayRecursionLimit = 10;

    cam.render(scenery);

}