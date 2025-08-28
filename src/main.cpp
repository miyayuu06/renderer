// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "renderer_utils.h"
#include "camera.h"
#include "material.h"
#include "texture.h"

#include "bvh.h"

#include "sphere.h"
#include "quad.h"
#include "triangle.h"
#include "disk.h"


using namespace Renderer;

void coverOfChapterOne() {

    HittableList scenery;

    Lambertian* ground = new Lambertian(new Checkered(0.32, Vec3(.2, .3, .1), Vec3(.9, .9, .9)));
    scenery.add(new Sphere(Vec3(0, -1000, 0), 1000, ground));

    for (int a = -7; a < 7; a++) {
        for (int b = -7; b < 7; b++) {
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

    scenery = HittableList(new BVH(scenery));

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

void checkeredSpheres() {
    HittableList world;

    auto checker = new Checkered(0.32, Vec3(.2, .3, .1), Vec3(.9, .9, .9));

    //world.add(new Sphere(Vec3(0, -10, 0), 10, new Lambertian(checker)));
    world.add(new Sphere(Vec3(0, 10, 0), 10, new Lambertian(checker)));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.width = 400;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.verticalViewAngle = 20;
    cam.lookfrom = Vec3(13, 2, -3);
    cam.lookat = Vec3(0, 0, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;
    cam.focusDistance = 1.0;

    cam.render(world);
}

void earth() {
    HittableList world;
    ImageTexture* texture = new ImageTexture("C:/users/yunaf/Documents/projects/renderer/MixedMedia/earthmap.jpg");
    //ImageTexture* texture = new ImageTexture("C:/users/yunaf/Desktop/elena.jpg");
    Lambertian* surface = new Lambertian(texture);

    world.add(new Sphere(Vec3(0, 0, 0), 2, surface));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.width = 400;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.verticalViewAngle = 20;
    //cam.lookfrom = Vec3(6, 0, -8);
    cam.lookfrom = Vec3(12, 0, 0);
    cam.lookat = Vec3(0, 0, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;
    cam.focusDistance = 1.0;

    cam.render(world);
}

void quads() {
    HittableList world;
    ImageTexture* texture = new ImageTexture("C:/users/yunaf/Desktop/luka.jpg");
    Lambertian* green= new Lambertian(texture);

    Lambertian* red = new Lambertian(Vec3(1.0, 0.2, 0.2));
    Lambertian* blue = new Lambertian(Vec3(0.2, 0.2, 1.0));
    Lambertian* orange = new Lambertian(Vec3(1.0, 0.5, 0.0));
    Lambertian* teal = new Lambertian(Vec3(0.2, 0.8, 0.8));

    world.add(new Quad(Vec3(-3, -2, -5), Vec3(0, 0, 4), Vec3(0, 4, 0), red));
    //world.add(new Triangle(Vec3(-2, -2, 0), Vec3(4, 0, 0), Vec3(2, 4, 0), green));
    //world.add(new Disk(Vec3(-2, 2, 0), Vec3(0, 4, 0), Vec3(4, 0, 0), green, 2.0));


    //DISK TO BE IMPLEMENTED


    world.add(new Quad(Vec3(3, -2, -1), Vec3(0, 0, -4), Vec3(0, 4, 0), blue));
    world.add(new Quad(Vec3(-2, 3, -1), Vec3(4, 0, 0), Vec3(0, 0, -4), orange));
    world.add(new Quad(Vec3(-2, -3, -5), Vec3(4, 0, 0), Vec3(0, 0, 4), teal));

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = 400;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.verticalViewAngle = 80;
    cam.lookfrom = Vec3(0, 0, -9);
    cam.lookat = Vec3(0, 0, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;
    cam.focusDistance = 1.0;

    cam.render(world);
}

void perlinTest() {
    HittableList world;

    NoiseTexture* pertext = new NoiseTexture();
    world.add(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(pertext)));
    world.add(new Sphere(Vec3(0, 2, 0), 2, new Lambertian(pertext)));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.width = 400;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 50;

    cam.verticalViewAngle = 20;
    cam.lookfrom = Vec3(13, 2, -3);
    cam.lookat = Vec3(0, 0, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;
    cam.focusDistance = 0.1;

    cam.render(world);
}

int main()
{
    //coverOfChapterOne();
    //checkeredSpheres();
    //earth();
    //quads();
    perlinTest();
}