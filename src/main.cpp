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

    scenery.add(new Sphere(Vec3(0.0, 0.0, 1.0), 0.5));
    scenery.add(new Sphere(Vec3(0.0, -100.5, 1.0), 100));

    Camera cam;
    cam.width = 600;
    cam.aspectRatio = 1.0;
    cam.samplesPerPixel = 50;
    cam.rayRecursionLimit = 50;

    cam.render(scenery);

}