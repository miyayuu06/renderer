#include "camera.h"
#include "color.h"
#include "stb_image_write.h"

#include <iostream>

namespace Renderer {
    Camera::Camera() {

    }

    Vec3 Camera::ray_color(HittableList& scenery, Ray& r) {

        // Possible collision with hittables

        HitProperties record;
        Interval rangeOfRender(0.0001, INFINITY);
        if (scenery.hit(rangeOfRender, r, record)) {
            return (record.normal + Vec3(1.0, 1.0, 1.0)) * 0.5;
        }

        // Background

        Vec3 unitVec3tor = r.dir().norm();
        double a = (unitVec3tor.y + 1.0) * 0.5;
        return (Vec3(1.0, 1.0, 1.0) * (1.0 - a)) + (Vec3(0.5, 0.7, 1.0) * a);
    }

    void Camera::initialize() {
        center = Vec3(0.0, 0.0, 0.0);
        height = int(width / aspectRatio);
        CHANNEL_NUM = 3;

        // Initialize Viewport
        double near = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (double(width) / height);

        Vec3 viewportHorizontal(viewportWidth, 0.0, 0.0);
        Vec3 viewportVertical(0.0, -viewportHeight, 0.0);
        deltaH = viewportHorizontal * (1.0 / width);
        deltaV = viewportVertical * (1.0 / height);

        // Upper left coordinates

        upperLeftCorner = center + Vec3(0.0, 0.0, near) + (viewportHorizontal * -0.5) + (viewportVertical * -0.5);
        pixel00 = upperLeftCorner + (deltaH + deltaV) * 0.5;

    }

    void Camera::render(HittableList& scenery) {
        uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

        uint32_t index = 0;

        for (uint32_t i = 0; i < height; i++) {
            std::cout << "Rendering row: " << i << std::endl;
            for (uint32_t j = 0; j < width; j++) {
                const Vec3 pixel = pixel00 + (deltaV * i) + (deltaH * j);
                const Vec3 rayDirection = pixel - center;
                Ray ray(center, rayDirection);

                Vec3 color = ray_color(scenery, ray);

                Color::writeColor(pixels, index, color);
            }
        }

        if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
            std::cout << "Hubo un error.\n";
        }

        delete[] pixels;

    }

}