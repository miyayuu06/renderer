#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "camera.h"
#include "color.h"
#include "stb_image_write.h"

#include "renderer_utils.h"
#include "material.h"

#include <iostream>
#include <thread>

namespace Renderer {
    Camera::Camera() {
    }

    Vec3 Camera::ray_color(const HittableList& scenery, const Ray& r, int depth) {
        if (depth <= 0) {
            return Vec3(0.0);
        }

        // Possible collision with hittables
        HitProperties record;
        Interval rangeOfRender(0.001, INFINITY);

        if (!scenery.hit(rangeOfRender, r, record)) {
            return background;
        }

        Ray scattered;
        Vec3 atenuation;
        Vec3 emissionColor = record.mat->emitted(record.u, record.v, record.intersectionPoint);

        if (!record.mat->scatter(r, record, atenuation, scattered)) {
            return emissionColor;
        }

        Vec3 scatterColor = Vec3::Vec3Mult(atenuation, ray_color(scenery, scattered, depth - 1));

        return emissionColor + scatterColor;
    }

    void Camera::initialize() {
        center = lookfrom;

        height = int(width / aspectRatio);
        printedRows = height;

        CHANNEL_NUM = 3;
        samplePixelProportion = 1.0 / samplesPerPixel;

        // Initialize Viewport
        double theta = degreesToRadians(verticalViewAngle);
        double h = std::tan(theta / 2);
        //double near = (lookfrom - lookat).length();
        double viewportHeight = 2 * h * focusDistance;
        double viewportWidth = viewportHeight * (double(width) / height);

        // Initialize camera vector parameters
        w = (lookfrom - lookat).norm();
        u = (up.cross(w)).norm();
        v = w.cross(u);

        // Viewport vectors
        Vec3 viewportHorizontal = -u * viewportWidth;
        Vec3 viewportVertical = -v * viewportHeight;

        deltaH = viewportHorizontal * 1.0 / width;
        deltaV = viewportVertical * 1.0 / height;

        // Upper left coordinates

        upperLeftCorner = center - (w * focusDistance) - (viewportHorizontal + viewportVertical) / 2;
        pixel00 = upperLeftCorner + (deltaH + deltaV) * 0.5;

        double focusRadius = focusDistance * std::tan(degreesToRadians(defocusAngle/2));
        focusDiskH = u * focusRadius;
        focusDiskV = v * focusRadius;

    }

    void Camera::sectionRender(const HittableList& scenery, uint8_t* pixels) {
        while (printedRows >= 0) {
            int i = printedRows.fetch_sub(1) - 1;
            std::cout << "Remaining rows: " << i << std::endl;

            if (i < 0) {
                return;
            }

            for (int j = 0; j < width; j++) {
                Vec3 pixelColor(0);
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray ray = get_ray(j, i);

                    pixelColor = pixelColor + ray_color(scenery, ray, rayRecursionLimit);
                }
                pixelColor = pixelColor * samplePixelProportion;
                uint32_t index = (i * width + j) * CHANNEL_NUM;
                Color::writeColor(pixels, index, pixelColor);
            }
        }
    }

    void Camera::render(const HittableList& scenery) {
        initialize();

        uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

        int numberOfThreads = 32;

        std::vector<std::thread> threads;

        for (int i = 0; i < numberOfThreads; i++) {
            threads.push_back(std::thread(&Camera::sectionRender, this, scenery, pixels));
        }

        for (auto &t : threads) {
            t.join();
        }

        if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
            std::cout << "Hubo un error.\n";
        }

        delete[] pixels;

    }

    Ray Camera::get_ray(int width, int height) const {
        Vec3 offset = sampleSquare();
        Vec3 pixelPosition = pixel00 + deltaH*(offset.x + width) + deltaV* (offset.y + height);
        Vec3 rayOrigin = (defocusAngle <= 0) ? center : diskSample();
        Vec3 rayDir = (pixelPosition - rayOrigin).norm();
        double rayTime = random();
        return Ray(rayOrigin, rayDir, rayTime);
    }

    Vec3 Camera::sampleSquare() const {
        return Vec3(random() - 0.5, random() - 0.5, 0);
    }

    Vec3 Camera::diskSample() const {
        Vec3 p = Vec3::randomUnitVectorInDisk();
        return center + focusDiskH * p[0] + focusDiskV * p[1];
    }

}