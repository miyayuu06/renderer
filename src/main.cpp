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

    Lambertian* ground = new Lambertian(Vec3(0.5, 0.5, 0.5));
    scenery.add(new Sphere(Vec3(0, -1000, 0), 1000, ground));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random();
            Vec3 center(a + 0.9 * random(), 0.2, b + 0.9 * random());

            if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                Material* sphereMaterial;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vec3::random();
                    sphereMaterial = new Lambertian(albedo);
                    Vec3 c2 = center + Vec3(0, randomRealNumber(0, 0.5), 0);
                    scenery.add(new Sphere(center, c2, 0.2, sphereMaterial));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Vec3::random(0.5, 1);
                    auto fuzz = randomRealNumber(0, 0.5);
                    sphereMaterial = new Metal(albedo, fuzz);
                    scenery.add(new Sphere(center, 0.2, sphereMaterial));
                }
                else {
                    // glass
                    sphereMaterial = new Dielectric(1.5);
                    scenery.add(new Sphere(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = new Dielectric(1.5);
    scenery.add(new Sphere(Vec3(0, 1, 0), 1.0, material1));

    auto material2 = new Lambertian(Vec3(0.4, 0.2, 0.1));
    scenery.add(new Sphere(Vec3(-4, 1, 0), 1.0, material2));

    auto material3 = new Metal(Vec3(0.7, 0.6, 0.5), 0.0);
    scenery.add(new Sphere(Vec3(4, 1, 0), 1.0, material3));

    Camera cam;
    cam.width = 800;
    cam.aspectRatio = 16.0 / 9.0;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.verticalViewAngle = 20;

    cam.lookfrom = Vec3(13, 2, -3);
    cam.lookat = Vec3(0, 0, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0.6;
    cam.focusDistance = 10.0;

    cam.render(scenery);

}