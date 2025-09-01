// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "renderer_utils.h"
#include "camera.h"
#include "material.h"
#include "constant_medium.h"

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
    cam.background = Vec3(0.70, 0.80, 1.00);

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
    cam.background = Vec3(0.70, 0.80, 1.00);

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
    cam.background = Vec3(0.70, 0.80, 1.00);

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
    cam.background = Vec3(0.70, 0.80, 1.00);

    cam.render(world);
}

void perlinTest() {
    HittableList world;

    NoiseTexture* pertext = new NoiseTexture(4);
    world.add(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(pertext)));
    world.add(new Sphere(Vec3(0, 2, 0), 2, new Lambertian(pertext)));

    auto difflight = new Light(Vec3(4, 4, 4));

    world.add(new Sphere(Vec3(0, 7, 0), 2, difflight));
    world.add(new Quad(Vec3(3, 1, 2), Vec3(2, 0, 0), Vec3(0, 2, 0), difflight));

    Camera cam;

    cam.aspectRatio = 16.0 / 9.0;
    cam.width = 1200;
    cam.samplesPerPixel = 500;
    cam.rayRecursionLimit = 100;

    cam.verticalViewAngle = 20;
    cam.lookfrom = Vec3(26, 3, -6);
    cam.lookat = Vec3(0, 2, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;
    cam.focusDistance = 0.1;

    cam.background = Vec3(0.0);

    cam.render(world);
}

void cornellBox() {
    HittableList world;

    auto red = new Lambertian(Vec3(.65, .05, .05));
    auto white = new Lambertian(Vec3(.73, .73, .73));
    auto green = new Lambertian(Vec3(.12, .45, .15));
    auto light = new Light(Vec3(15, 15, 15));

    world.add(new Quad(Vec3(555, 0, -555), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    world.add(new Quad(Vec3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, -555), red));
    world.add(new Quad(Vec3(343, 554, -332), Vec3(-130, 0, 0), Vec3(0, 0, 105), light));
    world.add(new Quad(Vec3(0, 0, -555), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    world.add(new Quad(Vec3(555, 555, -555), Vec3(-555, 0, 0), Vec3(0, 0, 555), white));
    world.add(new Quad(Vec3(0, 555, -555), Vec3(555, 0, 0), Vec3(0, -555, 0), white));

    Hittable* box1 = Quad::box(Vec3(), Vec3(165, 330, -165), white);
    box1 = new RotationY(box1, 15);
    box1 = new Translation(box1, Vec3(265, 0, -295));
    world.add(box1);

    Hittable* box2 = Quad::box(Vec3(), Vec3(165, 165, -165), white);
    box2 = new RotationY(box2, -18);
    box2 = new Translation(box2, Vec3(130, 0, -65));
    world.add(box2);

    
    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = 450;
    cam.samplesPerPixel = 100;
    cam.rayRecursionLimit = 20;
    cam.background = Vec3(0);

    cam.verticalViewAngle = 40;
    cam.lookfrom = Vec3(278, 278, 800);
    cam.lookat = Vec3(278, 278, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    cam.render(world);
}

void cornellSmoke() {
    HittableList world;

    auto red = new Lambertian(Vec3(.65, .05, .05));
    auto white = new Lambertian(Vec3(.73, .73, .73));
    auto green = new Lambertian(Vec3(.12, .45, .15));
    auto light = new Light(Vec3(7));

    world.add(new Quad(Vec3(555, 0, -555), Vec3(0, 555, 0), Vec3(0, 0, 555), green));
    world.add(new Quad(Vec3(0, 0, 0), Vec3(0, 555, 0), Vec3(0, 0, -555), red));
    world.add(new Quad(Vec3(442, 554, -427), Vec3(-330, 0, 0), Vec3(0, 0, 305), light));
    world.add(new Quad(Vec3(0, 0, -555), Vec3(555, 0, 0), Vec3(0, 0, 555), white));
    world.add(new Quad(Vec3(555, 555, -555), Vec3(-555, 0, 0), Vec3(0, 0, 555), white));
    world.add(new Quad(Vec3(0, 555, -555), Vec3(555, 0, 0), Vec3(0, -555, 0), white));

    Hittable* box1 = Quad::box(Vec3(), Vec3(165, 330, 165), white);
    box1 = new RotationY(box1, 15);
    box1 = new Translation(box1, Vec3(320, 0, -500));

    Hittable* box2 = Quad::box(Vec3(), Vec3(165, 165, 165), white);
    box2 = new RotationY(box2, -18);
    box2 = new Translation(box2, Vec3(100, 0, -250));

    //world.add(box1);
    //world.add(box2);

    world.add(new ConstantMedium(0.01, box1, Vec3()));
    world.add(new ConstantMedium(0.01, box2, Vec3(1)));


    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = 200;
    cam.samplesPerPixel = 200;
    cam.rayRecursionLimit = 50;
    cam.background = Vec3(0);

    cam.verticalViewAngle = 40;
    cam.lookfrom = Vec3(278, 278, 800);
    cam.lookat = Vec3(278, 278, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    cam.render(world);
}

int main()
{
    //srand(time(NULL));
    
    switch (7) {
        case 1:
            coverOfChapterOne(); break;
        case 2:
            checkeredSpheres(); break;
        case 3:
            earth(); break;
        case 4:
            quads(); break;
        case 5:
            perlinTest(); break;
        case 6:
            cornellBox(); break;
        case 7:
            cornellSmoke(); break;
    }
}