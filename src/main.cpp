// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#include "renderer_utils.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"


using namespace Renderer;

int main()
{

    HittableList scenery;

    Lambertian* ground = new Lambertian(Vec3(0.8, 0.8, 0));
    Lambertian* middle = new Lambertian(Vec3(0.8, 0.2, 0));
    Dielectric* metal1 = new Dielectric(1.00 / 1.33);
    Metal* metal2 = new Metal(Vec3(0.8, 0.8, 0.8), 0.0);

    scenery.add(new Sphere(Vec3(0.0, -100.5, 1.0), 100.0, ground));
    scenery.add(new Sphere(Vec3(0.0, 0.0, 1.2), 0.5, middle));
    scenery.add(new Sphere(Vec3(-1.0, 0.0, 1.0), 0.5, metal1));
    scenery.add(new Sphere(Vec3(1.0, 0.0, 1.0), 0.5, metal2));

    Camera cam;
    cam.width = 800;
    cam.aspectRatio = 16.0 / 9.0;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 20;

    cam.render(scenery);

}