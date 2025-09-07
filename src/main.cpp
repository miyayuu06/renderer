// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

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

    Hittable* box1 = box(Vec3(), Vec3(165, 330, -165), white);
    box1 = new RotationY(box1, 15);
    box1 = new Translation(box1, Vec3(265, 0, -295));
    world.add(box1);

    Hittable* box2 = box(Vec3(), Vec3(165, 165, -165), white);
    box2 = new RotationY(box2, -18);
    box2 = new Translation(box2, Vec3(130, 0, -65));
    world.add(box2);

    
    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = 600;
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

    Hittable* box1 = box(Vec3(), Vec3(165, 330, 165), white);
    box1 = new RotationY(box1, 15);
    box1 = new Translation(box1, Vec3(320, 0, -500));

    Hittable* box2 = box(Vec3(), Vec3(165, 165, 165), white);
    box2 = new RotationY(box2, -18);
    box2 = new Translation(box2, Vec3(100, 0, -250));

    //world.add(box1);
    //world.add(box2);

    world.add(new ConstantMedium(0.01, box1, Vec3(1, 0, 0)));
    world.add(new ConstantMedium(0.01, box2, Vec3(1)));

    //world = HittableList(new BVH(world));

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = 400;
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

void final_scene(int image_width, int samples_per_pixel, int max_depth) {
    HittableList boxes1;
    auto ground = new Lambertian(Vec3(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = randomRealNumber(1, 101);
            auto z1 = z0 + w;

            boxes1.add(box(Vec3(x0, y0, z0), Vec3(x1, y1, z1), ground));
        }
    }

    HittableList world;

    world.add(new BVH(boxes1));

    auto light = new Light(Vec3(7, 7, 7));
    world.add(new Quad(Vec3(123, 554, 147), Vec3(300, 0, 0), Vec3(0, 0, 265), light));

    auto center1 = Vec3(400, 400, 200);
    auto center2 = center1 + Vec3(30, 0, 0);
    auto sphere_material = new Lambertian(Vec3(0.7, 0.3, 0.1));
    world.add(new Sphere(center1, center2, 50, sphere_material));

    world.add(new Sphere(Vec3(260, 150, 45), 50, new Dielectric(1.5)));
    world.add(new Sphere(Vec3(0, 150, 145), 50, new Metal(Vec3(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = new Sphere(Vec3(360, 150, 145), 70, new Dielectric(1.5));
    world.add(boundary);
    world.add(new ConstantMedium(0.2, boundary, Vec3(0.2, 0.4, 0.9)));
    boundary = new Sphere(Vec3(0, 0, 0), 5000, new Dielectric(1.5));
    world.add(new ConstantMedium(0.0001, boundary, Vec3(1, 1, 1)));

    auto emat = new Lambertian(new ImageTexture("C:/users/yunaf/Documents/projects/renderer/MixedMedia/earthmap.jpg"));
    world.add(new Sphere(Vec3(400, 200, 400), 100, emat));
    auto pertext = new NoiseTexture(0.2);
    world.add(new Sphere(Vec3(220, 280, 300), 80, new Lambertian(pertext)));

    HittableList boxes2;
    auto white = new Lambertian(Vec3(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(new Sphere(Vec3::random(0, 165), 10, white));
    }

    world.add(new Translation(
        new RotationY(
            new BVH(boxes2), 15),
        Vec3(-100, 270, 395)
    )
    );

    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = image_width;
    cam.samplesPerPixel = samples_per_pixel;
    cam.rayRecursionLimit = max_depth;
    cam.background = Vec3(0, 0, 0);

    cam.verticalViewAngle = 40;
    cam.lookfrom = Vec3(478, 278, -600);
    cam.lookat = Vec3(278, 278, 0);
    cam.up = Vec3(0, 1, 0);

    cam.defocusAngle = 0;

    cam.render(world);
}

HittableList* objread(const std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!";
        return new HittableList();
    }
    std::string s;

    HittableList* world = new HittableList();

    std::vector<Vec3> coordinates;
    std::vector<Vec3> textures;
    std::vector<Vec3> normals;

    Lambertian* tex = new Lambertian(Vec3(0.5));

    while (std::getline(file, s)) {
        std::istringstream line(s);
        std::string type;

        line >> type;

        if (type == "v") {
            float x, y, z;
            line >> x >> y >> z;
            coordinates.push_back(Vec3(x, y, z));
        }

        if (type == "vt") {
            float x, y, z;
            line >> x >> y >> z;
            textures.push_back(Vec3(x, y, z));
        }

        if (type == "vn") {
            float x, y, z;
            line >> x >> y >> z;
            normals.push_back(Vec3(x, y, z));
        }

        if (type == "f") {
            std::vector<int> vIdx, tIdx, nIdx;
            std::string token;

            while (line >> token) {
                int v = 0, t = 0, n = 0;

                if (sscanf(token.c_str(), "%d/%d/%d", &v, &t, &n) == 3) {
                    vIdx.push_back(v - 1);
                    tIdx.push_back(t - 1);
                    nIdx.push_back(n - 1);
                }
                else if (sscanf(token.c_str(), "%d//%d", &v, &n) == 2) {
                    vIdx.push_back(v - 1);
                    nIdx.push_back(n - 1);
                }
                else if (sscanf(token.c_str(), "%d/%d", &v, &t) == 2) {
                    vIdx.push_back(v - 1);
                    tIdx.push_back(t - 1);
                }
                else if (sscanf(token.c_str(), "%d", &v) == 1) {
                    vIdx.push_back(v - 1);
                }
            }

            for (size_t i = 1; i + 1 < vIdx.size(); i++) {
                Vec3 v0 = coordinates[vIdx[0]];
                Vec3 v1 = coordinates[vIdx[i]];
                Vec3 v2 = coordinates[vIdx[i + 1]];

                Vec3 u = v2 - v0;
                Vec3 v = v1 - v0;

                world->add(new Triangle(v0, u, v, tex));
            }
        }
    }

    file.close();    

    return world;
}

HittableList* objmetal(const std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening the file!";
        return new HittableList();
    }
    std::string s;

    HittableList* world = new HittableList();

    std::vector<Vec3> coordinates;
    std::vector<Vec3> textures;
    std::vector<Vec3> normals;

    Metal* tex = new Metal(Vec3(0.8, 0.47, 0.14), 0.9);

    while (std::getline(file, s)) {
        std::istringstream line(s);
        std::string type;

        line >> type;

        if (type == "v") {
            float x, y, z;
            line >> x >> y >> z;
            coordinates.push_back(Vec3(x, y, z));
        }

        if (type == "vt") {
            float x, y, z;
            line >> x >> y >> z;
            textures.push_back(Vec3(x, y, z));
        }

        if (type == "vn") {
            float x, y, z;
            line >> x >> y >> z;
            normals.push_back(Vec3(x, y, z));
        }

        if (type == "f") {
            std::vector<int> vIdx, tIdx, nIdx;
            std::string token;

            while (line >> token) {
                int v = 0, t = 0, n = 0;

                if (sscanf(token.c_str(), "%d/%d/%d", &v, &t, &n) == 3) {
                    vIdx.push_back(v - 1);
                    tIdx.push_back(t - 1);
                    nIdx.push_back(n - 1);
                }
                else if (sscanf(token.c_str(), "%d//%d", &v, &n) == 2) {
                    vIdx.push_back(v - 1);
                    nIdx.push_back(n - 1);
                }
                else if (sscanf(token.c_str(), "%d/%d", &v, &t) == 2) {
                    vIdx.push_back(v - 1);
                    tIdx.push_back(t - 1);
                }
                else if (sscanf(token.c_str(), "%d", &v) == 1) {
                    vIdx.push_back(v - 1);
                }
            }

            for (size_t i = 1; i + 1 < vIdx.size(); i++) {
                Vec3 v0 = coordinates[vIdx[0]];
                Vec3 v1 = coordinates[vIdx[i]];
                Vec3 v2 = coordinates[vIdx[i + 1]];

                Vec3 u = v2 - v0;
                Vec3 v = v1 - v0;

                world->add(new Triangle(v0, u, v, tex));
            }
        }
    }

    file.close();

    return world;
}

void objRender(HittableList* world, int size) {
    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = size;
    cam.samplesPerPixel = 50;
    cam.rayRecursionLimit = 20;
    cam.background = Vec3(0.7);

    cam.verticalViewAngle = 40;
    cam.lookfrom = Vec3(100, -100, 50);
    cam.lookat = Vec3(0, 0, 25);
    cam.up = Vec3(0, 0, 1);

    cam.defocusAngle = 0;

    cam.render(world);
}

void skullCamera(HittableList* world, int size) {
    Camera cam;

    cam.aspectRatio = 1.0;
    cam.width = size;
    cam.samplesPerPixel = 50;
    cam.rayRecursionLimit = 20;
    cam.background = Vec3(0.7);

    cam.verticalViewAngle = 40;
    cam.lookfrom = Vec3(50, -70, 20);
    cam.lookat = Vec3(0, 0, 20);
    cam.up = Vec3(0, 0, 1);

    cam.defocusAngle = 0;

    cam.render(world);
}

int main()
{
    //srand(time(NULL));
    
    double timeStart = time(NULL);

    switch (10) {
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
        case 8:
            final_scene(1200, 1000, 40); break;
        case 9: {
            std::string filename = "C:/Users/yunaf/Desktop/Skull/Bird.obj";
            objRender(objread(filename), 600);
            break;
        }
        case 10: {
            std::string file = "C:/Users/yunaf/Desktop/Skull/Skull.obj";
            skullCamera(objmetal(file), 600);
            break;
        }
    }

    double timeEnd = time(NULL);

    std::cout << std::endl << "The image took " << (int) (timeEnd - timeStart) << " seconds to render." << std::endl;
}