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
    Lambertian* middle = new Lambertian(Vec3(0.1, 0.2, 0.5));
    Dielectric* left = new Dielectric(1.5);
    Dielectric* bubble = new Dielectric(1.0 / 1.5);
    Metal* right = new Metal(Vec3(0.8, 0.6, 0.2), 0.0);

    scenery.add(new Sphere(Vec3(0.0, -100.5, 1.0), 100.0, ground));
    scenery.add(new Sphere(Vec3(0.0, 0.0, 1.2), 0.5, middle));
    scenery.add(new Sphere(Vec3(-1.0, 0.0, 1.0), 0.5, left));
    scenery.add(new Sphere(Vec3(-1.0, 0.0, 1.0), 0.4, bubble));
    //scenery.add(new Sphere(Vec3(-1.0, 0.0, 3.0), 0.3, right));
    scenery.add(new Sphere(Vec3(1.0, 0.0, 1.0), 0.5, right));

    Camera cam;
    cam.width = 800;
    cam.aspectRatio = 24.0 / 9.0;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.render(scenery);

}