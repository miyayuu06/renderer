#include "camera.h"
#include "color.h"
#include "stb_image_write.h"

#include "renderer_utils.h"
#include "material.h"

#include <iostream>

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

        if (scenery.hit(rangeOfRender, r, record)) {
            Ray scattered;
            Vec3 atenuation;
            if (record.mat->scatter(r, record, atenuation, scattered)) {
                return Vec3::Vec3Mult(atenuation, ray_color(scenery, scattered, depth - 1));
            }
            return Vec3(0.0);
        }

        // Background
        Vec3 unitVec3tor = r.dir().norm();
        double a = (unitVec3tor.y + 1.0) * 0.5;
        return Vec3(1.0 - a) + Vec3(0.5, 0.7, 1.0) * a;
    }

    void Camera::initialize() {
        center = lookfrom;

        height = int(width / aspectRatio);
        CHANNEL_NUM = 3;
        samplePixelProportion = 1.0 / samplesPerPixel;

        // Initialize Viewport
        double theta = degreesToRadians(verticalViewAngle);
        double h = std::tan(theta / 2);
        double near = (lookfrom - lookat).length();
        double viewportHeight = 2 * h * near;
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

        upperLeftCorner = center - (w * near) - (viewportHorizontal + viewportVertical) / 2;
        pixel00 = upperLeftCorner + (deltaH + deltaV) * 0.5;

    }

    void Camera::render(const HittableList& scenery) {
        initialize();

        uint8_t* pixels = new uint8_t[width * height * CHANNEL_NUM];

        uint32_t index = 0;

        for (int i = 0; i < height; i++) {
            std::cout << "Rendering row: " << i << std::endl;
            for (int j = 0; j < width; j++) {
                Vec3 pixelColor(0);
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray ray = get_ray(j, i);

                    pixelColor = pixelColor + ray_color(scenery, ray, rayRecursionLimit);
                }
                pixelColor = pixelColor * samplePixelProportion;
                Color::writeColor(pixels, index, pixelColor);
            }
        }

        if (!stbi_write_png("C:/Users/yunaf/Desktop/testimage.png", width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM)) {
            std::cout << "Hubo un error.\n";
        }

        delete[] pixels;

    }

    Ray Camera::get_ray(int width, int height) const {
        Vec3 offset = sampleSquare();
        Vec3 pixelPosition = pixel00 + deltaH*(offset.x + width) + deltaV* (offset.y + height);
        Vec3 rayDir = pixelPosition - center;
        return Ray(center, rayDir);
    }

    Vec3 Camera::sampleSquare() const {
        return Vec3(random() - 0.5, random() - 0.5, 0);
    }

}